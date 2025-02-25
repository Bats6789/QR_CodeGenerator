#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "QRcode.h"
#include "image.h"
#include "image_export.h"

int main(int argc, char **argv) {
    image_t image;
    QRcode_t QRcode;
    const char *message;

    if (argc == 2) {
        message = argv[1];
    } else {
        message = "TEST123";
    }
	puts(message);

    QRcode = generate_QRcode(message, ANY_VERSION, ANY_MASK, QR_L);

    image = QRcodeToImage(QRcode);

    if (export_to_png("test.png", image) != 0) {
        perror("export");
        return EXIT_FAILURE;
    }

    free_image(image);

    return 0;
}
