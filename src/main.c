#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "QRcode.h"
#include "image.h"
#include "image_import.h"
#include "image_export.h"
#include "version.h"

extern char *optarg;
extern int optind, opterr, optopt;

void print_help(void);
void print_version(void);
char *read_file(const char *input_filename);

int main(int argc, char **argv) {
    image_t image = {0, 0, NULL};
	image_t logo_image = {0, 0, NULL};
    QRcode_t QRcode = {0, 0, NULL};
    int opt = 0;
    int value = 0;
    char ans = '\0';
    char *message = NULL;
    char *check = NULL;
    const char *output_filename = "test.png";
    const char *input_filename = NULL;
    bool force = false;
	bool embed_logo = false;
    format_t format = {PIXEL_PER_MODULE, WHITE, BLACK};
    pixel_res_t pixel_res = {{.color = 0}, false};
	point_t start_embed_pt = {0, 0};
	point_t stop_embed_pt = {0, 0};

    while ((opt = getopt(argc, argv, "C:c:d:fhi:l:o:v")) != -1) {
        switch (opt) {
            case 'C':
                pixel_res = str_to_color(optarg);

                if (!pixel_res.valid) {
                    fprintf(stderr, "ERROR: %s is not a valid color\n", optarg);
                    return EXIT_FAILURE;
                }

                format.foreground = pixel_res.pixel;
                break;
            case 'c':
                pixel_res = str_to_color(optarg);

                if (!pixel_res.valid) {
                    fprintf(stderr, "ERROR: %s is not a valid color\n", optarg);
                    return EXIT_FAILURE;
                }

                format.background = pixel_res.pixel;
                break;
            case 'd':
                errno = 0;  // set to zero to detect errors with strtod
                value = strtol(optarg, &check, 0);

                if (errno != 0) {
                    perror("Value Error");
                    return EXIT_FAILURE;
                }

                if (value == 0 && optarg == check) {
                    fputs("ERROR: No value detected\n", stderr);
                    return EXIT_FAILURE;
                }

                if (*check != '\0' || *optarg == '\0') {
                    fputs("ERROR: Failed to convert argument to value - d\n", stderr);
                    return EXIT_FAILURE;
                }

                if (value <= 0) {
                    fputs("ERROR: Pixel density must be at least 1\n", stderr);
                    return EXIT_FAILURE;
                }

                format.pixel_per_module = value;
                break;
            case 'f':
                force = true;
                break;
            case 'h':
                print_help();
                return EXIT_FAILURE;
            case 'i':
                input_filename = optarg;
                break;
            case 'l':
				logo_image = import_image(optarg);
				if (logo_image.pixels == NULL) {
					perror(optarg);
					return EXIT_FAILURE;
				}
				embed_logo = true;
                break;
            case 'o':
                output_filename = optarg;
                break;
            case 'v':
                print_version();
                return EXIT_SUCCESS;
            case '?':
            default:
                fprintf(stderr, "ERROR: Unknown argument: %c\n", opt);
                return EXIT_FAILURE;
        }
    }

    if (!force && access(output_filename, F_OK) == 0) {
        printf("%s: already exists. Is it okay to overwrite? (Y/N) ", output_filename);
        ans = getchar();
        if (ans == 'N' || ans == 'n') {
            return EXIT_SUCCESS;
        }
    }

    if (optind >= argc && input_filename == NULL) {
        fputs("ERROR: Missing argument <text>\n", stderr);
        return EXIT_FAILURE;
    }

    if (input_filename == NULL) {
        message = argv[optind];
    } else {
        message = read_file(input_filename);
        if (message == NULL) {
            perror(input_filename);
            return EXIT_FAILURE;
        }
    }

    puts(message);

    QRcode = generate_QRcode(message, ANY_VERSION, ANY_MASK, QR_H);

    image = QRcodeToImage(QRcode, format);

	if (embed_logo) {
		start_embed_pt.x = image.width * 0.375;
		start_embed_pt.y = image.height * 0.375;
		stop_embed_pt.x = image.width * 0.625;
		stop_embed_pt.y = image.height * 0.625;
		embed_img(image, logo_image, start_embed_pt, stop_embed_pt);
		free_image(logo_image);
	}

    if (export_to_png(output_filename, image) != 0) {
        perror("export");
        return EXIT_FAILURE;
    }

    free_image(image);
    if (input_filename != NULL) {
        free(message);
    }

    return 0;
}

void print_help(void) {
    puts("Usage: QRCode [-dfhiov] <text>");
    puts("");
    puts("Generate QR code for <text>.");
    puts("");
    puts("Options:");
    puts("  -C <color>        The foreground color. (Default 000000 or black)");
    puts("  -c <color>        The background color. (Default FFFFFF or white)");
    puts(
        "  -d <density>      The number of pixels per module. Must be greater "
        "than 1.");
    puts("                    (Default 8)");
    puts("  -f                Force file overwrites.");
    puts("  -h                Print this message.");
    puts("  -i <file>         Input filename.");
    puts("  -l <file>         Logo to embed in the QR code.");
    puts("  -o <file>         Output filename. (Default test.png)");
    puts("  -v                Print the version");
}

void print_version(void) { printf("QRcode: v" QRCode_VERSION_STRING); }

char *read_file(const char *input_filename) {
    size_t sz = 100;
    size_t count = 0;
    char *contents = NULL;
    char c;
    FILE *file;

    file = fopen(input_filename, "r");
    if (file == NULL) {
        return NULL;
    }

    contents = malloc(sizeof *contents * sz);
    if (contents == NULL) {
        return NULL;
    }

    while ((c = fgetc(file)) != EOF) {
        contents[count++] = c;
        if (count >= sz) {
            sz += 100;
            contents = realloc(contents, sizeof *contents * sz);
            if (contents == NULL) {
                return NULL;
            }
        }
    }
    contents[count++] = '\0';

    fclose(file);

    return realloc(contents, sizeof *contents * count);
}
