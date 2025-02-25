#include <stdio.h>
#include <stdlib.h>

#include "QR_codewords.h"
#include "QRcode.h"
#include "bch.h"
#include "image.h"
#include "reed_solomon.h"

static void place_alignment(QRcode_t QRcode, QR_version_t version) {
    size_t sz = 0;
    size_t points[7];
    module_t default_on = {true, true};
    module_t default_off = {false, true};

    // quite versions without alignment
    switch (version) {
        case V1:
        case MV1:
        case MV2:
        case MV3:
        case MV4:
            return;
        case V2:
            points[sz++] = 6;
            points[sz++] = 18;
            break;
        case V3:
            points[sz++] = 6;
            points[sz++] = 22;
            break;
        case V4:
            points[sz++] = 6;
            points[sz++] = 26;
            break;
        case V5:
            points[sz++] = 6;
            points[sz++] = 30;
            break;
        case V6:
            points[sz++] = 6;
            points[sz++] = 34;
            break;
        case V7:
            points[sz++] = 6;
            points[sz++] = 22;
            points[sz++] = 38;
            break;
        case V8:
            points[sz++] = 6;
            points[sz++] = 24;
            points[sz++] = 42;
            break;
        case V9:
            points[sz++] = 6;
            points[sz++] = 26;
            points[sz++] = 46;
            break;
        case V10:
            points[sz++] = 6;
            points[sz++] = 28;
            points[sz++] = 50;
            break;
        case V11:
            points[sz++] = 6;
            points[sz++] = 30;
            points[sz++] = 54;
            break;
        case V12:
            points[sz++] = 6;
            points[sz++] = 32;
            points[sz++] = 58;
            break;
        case V13:
            points[sz++] = 6;
            points[sz++] = 34;
            points[sz++] = 62;
            break;
        case V14:
            points[sz++] = 6;
            points[sz++] = 26;
            points[sz++] = 46;
            points[sz++] = 66;
            break;
        case V15:
            points[sz++] = 6;
            points[sz++] = 26;
            points[sz++] = 48;
            points[sz++] = 70;
            break;
        case V16:
            points[sz++] = 6;
            points[sz++] = 26;
            points[sz++] = 50;
            points[sz++] = 74;
            break;
        case V17:
            points[sz++] = 6;
            points[sz++] = 30;
            points[sz++] = 54;
            points[sz++] = 78;
            break;
        case V18:
            points[sz++] = 6;
            points[sz++] = 30;
            points[sz++] = 56;
            points[sz++] = 82;
            break;
        case V19:
            points[sz++] = 6;
            points[sz++] = 30;
            points[sz++] = 58;
            points[sz++] = 86;
            break;
        case V20:
            points[sz++] = 6;
            points[sz++] = 34;
            points[sz++] = 62;
            points[sz++] = 90;
            break;
        case V21:
            points[sz++] = 6;
            points[sz++] = 28;
            points[sz++] = 50;
            points[sz++] = 72;
            points[sz++] = 94;
            break;
        case V22:
            points[sz++] = 6;
            points[sz++] = 26;
            points[sz++] = 50;
            points[sz++] = 74;
            points[sz++] = 98;
            break;
        case V23:
            points[sz++] = 6;
            points[sz++] = 30;
            points[sz++] = 54;
            points[sz++] = 78;
            points[sz++] = 102;
            break;
        case V24:
            points[sz++] = 6;
            points[sz++] = 28;
            points[sz++] = 54;
            points[sz++] = 80;
            points[sz++] = 106;
            break;
        case V25:
            points[sz++] = 6;
            points[sz++] = 32;
            points[sz++] = 58;
            points[sz++] = 84;
            points[sz++] = 110;
            break;
        case V26:
            points[sz++] = 6;
            points[sz++] = 30;
            points[sz++] = 58;
            points[sz++] = 86;
            points[sz++] = 114;
            break;
        case V27:
            points[sz++] = 6;
            points[sz++] = 34;
            points[sz++] = 62;
            points[sz++] = 90;
            points[sz++] = 118;
            break;
        case V28:
            points[sz++] = 6;
            points[sz++] = 26;
            points[sz++] = 50;
            points[sz++] = 74;
            points[sz++] = 98;
            points[sz++] = 122;
            break;
        case V29:
            points[sz++] = 6;
            points[sz++] = 30;
            points[sz++] = 54;
            points[sz++] = 78;
            points[sz++] = 102;
            points[sz++] = 126;
            break;
        case V30:
            points[sz++] = 6;
            points[sz++] = 26;
            points[sz++] = 52;
            points[sz++] = 78;
            points[sz++] = 104;
            points[sz++] = 130;
            break;
        case V31:
            points[sz++] = 6;
            points[sz++] = 30;
            points[sz++] = 56;
            points[sz++] = 82;
            points[sz++] = 118;
            points[sz++] = 134;
            break;
        case V32:
            points[sz++] = 6;
            points[sz++] = 34;
            points[sz++] = 60;
            points[sz++] = 86;
            points[sz++] = 112;
            points[sz++] = 138;
            break;
        case V33:
            points[sz++] = 6;
            points[sz++] = 30;
            points[sz++] = 58;
            points[sz++] = 86;
            points[sz++] = 114;
            points[sz++] = 142;
            break;
        case V34:
            points[sz++] = 6;
            points[sz++] = 34;
            points[sz++] = 62;
            points[sz++] = 90;
            points[sz++] = 118;
            points[sz++] = 146;
            break;
        case V35:
            points[sz++] = 6;
            points[sz++] = 30;
            points[sz++] = 54;
            points[sz++] = 78;
            points[sz++] = 102;
            points[sz++] = 126;
            points[sz++] = 150;
            break;
        case V36:
            points[sz++] = 6;
            points[sz++] = 24;
            points[sz++] = 50;
            points[sz++] = 76;
            points[sz++] = 102;
            points[sz++] = 128;
            points[sz++] = 154;
            break;
        case V37:
            points[sz++] = 6;
            points[sz++] = 28;
            points[sz++] = 54;
            points[sz++] = 80;
            points[sz++] = 106;
            points[sz++] = 132;
            points[sz++] = 158;
            break;
        case V38:
            points[sz++] = 6;
            points[sz++] = 32;
            points[sz++] = 58;
            points[sz++] = 84;
            points[sz++] = 110;
            points[sz++] = 136;
            points[sz++] = 162;
            break;
        case V39:
            points[sz++] = 6;
            points[sz++] = 26;
            points[sz++] = 54;
            points[sz++] = 82;
            points[sz++] = 110;
            points[sz++] = 138;
            points[sz++] = 166;
            break;
        case V40:
            points[sz++] = 6;
            points[sz++] = 30;
            points[sz++] = 58;
            points[sz++] = 86;
            points[sz++] = 114;
            points[sz++] = 142;
            points[sz++] = 170;
            break;
        default:
            break;
    }

    for (size_t i = 0; i < sz; ++i) {
        for (size_t j = 0; j < sz; ++j) {
            size_t row = points[i];
            size_t col = points[j];

            // exclude finder patterns
            if ((row < 8 && col < 8) || (row < 8 && col >= QRcode.width - 8) || (row >= QRcode.height - 8 && col < 8)) {
                continue;
            }

            for (size_t k = 0; k < 5; ++k) {
                QRcode.modules[(row - 2) * QRcode.width + (col - 2) + k] = default_on;
                QRcode.modules[(row - 1) * QRcode.width + (col - 2) + k] =
                    (k == 0 || k == 4) ? default_on : default_off;
                QRcode.modules[row * QRcode.width + (col - 2) + k] = (k == 1 || k == 3) ? default_off : default_on;
                QRcode.modules[(row + 1) * QRcode.width + (col - 2) + k] =
                    (k == 0 || k == 4) ? default_on : default_off;
                QRcode.modules[(row + 2) * QRcode.width + (col - 2) + k] = default_on;
            }
        }
    }
}

static bool is_ec_parsed(size_t *ec_loc, QR_version_params_t params) {
    for (size_t i = 0; i < params.block_count; ++i) {
        if (ec_loc[i] != params.blocks[i].err_sz) {
            return false;
        }
    }

    return true;
}

static bool is_data_parsed(size_t *data_loc, QR_version_params_t params) {
    for (size_t i = 0; i < params.block_count; ++i) {
        if (data_loc[i] != params.blocks[i].data_sz) {
            return false;
        }
    }

    return true;
}

static bool is_codewords_parsed(size_t *data_loc, size_t *ec_loc, QR_version_params_t params) {
    return is_data_parsed(data_loc, params) && is_ec_parsed(ec_loc, params);
}

QRcode_t generate_QRcode(const char *message, QR_recovery_t recovery) {
    int **ec;
    int **data = NULL;
    QRcode_t QRcode;
    size_t *data_loc = NULL;
    size_t *ec_loc = NULL;
    size_t byte_loc = 0;
    size_t block_loc = 0;
    module_t default_on = {true, true};
    module_t default_off = {false, true};
    QR_version_t version = V7;
    size_t sz = get_QR_size(version);
    size_t row = sz - 1;
    size_t col = sz - 1;

    QRcode.width = sz;
    QRcode.height = sz;
    QRcode.modules = malloc(sizeof *QRcode.modules * sz * sz);

    for (size_t i = 0; i < sz * sz; ++i) {
        QRcode.modules[i] = (module_t){false, false};
    }

    QR_version_params_t params = get_version_params(version, recovery);

    data = malloc(sizeof *data * params.block_count);
    ec = malloc(sizeof *ec * params.block_count);
    data_loc = calloc(params.block_count, sizeof *data_loc);
    ec_loc = calloc(params.block_count, sizeof *ec_loc);

	size_t total_data = 0;
	for (size_t i = 0; i < params.block_count; ++i) {
		total_data += params.blocks[i].data_sz;
	}
	int *tmp;
	generate_codewords(message, total_data, &tmp);

	size_t shift = 0;
	for (size_t i = 0; i < params.block_count; ++i) {
		data[i] = malloc(sizeof **data * params.blocks[i].data_sz);
		for (size_t j = 0; j < params.blocks[i].data_sz; ++j) {
			data[i][j] = tmp[shift + j];
		}
		shift += params.blocks[i].data_sz;
	}

    calculate_table();

    for (size_t i = 0; i < params.block_count; ++i) {
        reed_solomon(params.blocks[i].data_sz, data[i], params.blocks[i].err_sz, ec + i);
    }

    uint8_t byte = data[0][data_loc[0]++] & 0xFF;

    // finder pattern
    for (size_t i = 0; i < 7; ++i) {
        // top left
        QRcode.modules[i] = default_on;
        QRcode.modules[sz + i] = (i == 0 || i == 6) ? default_on : default_off;
        QRcode.modules[2 * sz + i] = (i == 1 || i == 5) ? default_off : default_on;
        QRcode.modules[3 * sz + i] = (i == 1 || i == 5) ? default_off : default_on;
        QRcode.modules[4 * sz + i] = (i == 1 || i == 5) ? default_off : default_on;
        QRcode.modules[5 * sz + i] = (i == 0 || i == 6) ? default_on : default_off;
        QRcode.modules[6 * sz + i] = default_on;

        // top right
        QRcode.modules[sz - 7 + i] = default_on;
        QRcode.modules[2 * sz - 7 + i] = (i == 0 || i == 6) ? default_on : default_off;
        QRcode.modules[3 * sz - 7 + i] = (i == 1 || i == 5) ? default_off : default_on;
        QRcode.modules[4 * sz - 7 + i] = (i == 1 || i == 5) ? default_off : default_on;
        QRcode.modules[5 * sz - 7 + i] = (i == 1 || i == 5) ? default_off : default_on;
        QRcode.modules[6 * sz - 7 + i] = (i == 0 || i == 6) ? default_on : default_off;
        QRcode.modules[7 * sz - 7 + i] = default_on;

        // bottom left
        QRcode.modules[(QRcode.height - 7) * sz + i] = default_on;
        QRcode.modules[(QRcode.height - 6) * sz + i] = (i == 0 || i == 6) ? default_on : default_off;
        QRcode.modules[(QRcode.height - 5) * sz + i] = (i == 1 || i == 5) ? default_off : default_on;
        QRcode.modules[(QRcode.height - 4) * sz + i] = (i == 1 || i == 5) ? default_off : default_on;
        QRcode.modules[(QRcode.height - 3) * sz + i] = (i == 1 || i == 5) ? default_off : default_on;
        QRcode.modules[(QRcode.height - 2) * sz + i] = (i == 0 || i == 6) ? default_on : default_off;
        QRcode.modules[(QRcode.height - 1) * sz + i] = default_on;
    }

    // buffer around finder
    for (size_t i = 0; i < 8; ++i) {
        // top left
        QRcode.modules[i * sz + 7] = default_off;
        QRcode.modules[7 * sz + i] = default_off;

        // top right
        QRcode.modules[(i + 1) * sz - 8] = default_off;
        QRcode.modules[8 * sz - 8 + i] = default_off;

        // bottom left
        QRcode.modules[(QRcode.height - i - 1) * sz + 7] = default_off;
        QRcode.modules[(QRcode.height - 8) * sz + i] = default_off;
    }

    // timing pattern
    for (size_t i = 0; i < sz - 16; ++i) {
        // horizontal
        QRcode.modules[6 * sz + 8 + i] = (i & 1) == 1 ? default_off : default_on;
        // vertical
        QRcode.modules[(8 + i) * sz + 6] = (i & 1) == 1 ? default_off : default_on;
    }

    place_alignment(QRcode, version);

    // reserve format from data
    // Note: The positions are hardcoded due to awkward skips for the first
    //       batch (top left). So the second batch is copied for consistency
    // top left
    QRcode.modules[8] = default_off;
    QRcode.modules[sz + 8] = default_off;
    QRcode.modules[2 * sz + 8] = default_off;
    QRcode.modules[3 * sz + 8] = default_off;
    QRcode.modules[4 * sz + 8] = default_off;
    QRcode.modules[5 * sz + 8] = default_off;
    QRcode.modules[7 * sz + 8] = default_off;
    QRcode.modules[8 * sz + 8] = default_off;
    QRcode.modules[8 * sz + 7] = default_off;
    QRcode.modules[8 * sz + 5] = default_off;
    QRcode.modules[8 * sz + 4] = default_off;
    QRcode.modules[8 * sz + 3] = default_off;
    QRcode.modules[8 * sz + 2] = default_off;
    QRcode.modules[8 * sz + 1] = default_off;
    QRcode.modules[8 * sz] = default_off;

    // split (bottom left and top right)
    QRcode.modules[9 * sz - 1] = default_off;
    QRcode.modules[9 * sz - 2] = default_off;
    QRcode.modules[9 * sz - 3] = default_off;
    QRcode.modules[9 * sz - 4] = default_off;
    QRcode.modules[9 * sz - 5] = default_off;
    QRcode.modules[9 * sz - 6] = default_off;
    QRcode.modules[9 * sz - 7] = default_off;
    QRcode.modules[9 * sz - 8] = default_off;
    QRcode.modules[(sz - 7) * sz + 8] = default_off;
    QRcode.modules[(sz - 6) * sz + 8] = default_off;
    QRcode.modules[(sz - 5) * sz + 8] = default_off;
    QRcode.modules[(sz - 4) * sz + 8] = default_off;
    QRcode.modules[(sz - 3) * sz + 8] = default_off;
    QRcode.modules[(sz - 2) * sz + 8] = default_off;
    QRcode.modules[(sz - 1) * sz + 8] = default_off;

    // reserve version from data if V7 or higher
	if (version >= V7) {
		for (size_t i = 0; i < 6; ++i) {
			for (size_t j = QRcode.height - 11; j < QRcode.height - 8; ++j) {
				QRcode.modules[j * sz + i] = default_off;
				QRcode.modules[i * sz + j] = default_off;
			}
		}
	}

    bool upwards = true;
    bool left = true;

    while (!is_codewords_parsed(data_loc, ec_loc, params) || byte_loc != 8) {
        // bool should_mask = (row + col) % 2 == 0;
        bool should_mask = ((row*col) % 3 + row * col) % 2 == 0;
        bool bit_val = (byte & (0x80 >> byte_loc)) == (0x80 >> byte_loc);

        if (should_mask) {
            QRcode.modules[row * sz + col].data = !bit_val;
        } else {
            QRcode.modules[row * sz + col].data = bit_val;
        }
        QRcode.modules[row * sz + col].used = true;

        if (left) {
            col--;
            left = false;
        } else {
            if (upwards) {
                if (row == 0) {
                    upwards = false;
                    col -= col == 7 ? 2 : 1;
                } else {
                    while (QRcode.modules[--row * sz + col].used) {
                        if (row == 0) {
                            break;
                        }
                    }

                    if (row == 0 && QRcode.modules[row * sz + col].used) {
                        upwards = false;
						if (version >= V7 && col == QRcode.width - 10) {
							col--;
						} else {
							col -= col == 7 ? 2 : 1;
							while (QRcode.modules[++row * sz + col].used) {
							}
						}
                    } else {
                        col++;
                    }
                }
            } else {
                if (row == sz - 1) {
                    upwards = true;
                    if (col == 9) {
                        row = sz - 9;
                    }
                    col -= col == 7 ? 2 : 1;
                } else {
                    while (QRcode.modules[++row * sz + col].used) {
                        if (row == sz - 1) {
                            break;
                        }
                    }

                    if (row == sz - 1 && QRcode.modules[row * sz + col].used) {
                        upwards = true;
                        col -= col == 7 ? 2 : 1;
                        while (QRcode.modules[--row * sz + col].used) {
                        }
                    } else {
                        col++;
                    }
                }
            }

            if (QRcode.modules[row * sz + col].used) {
                col--;
            } else {
                left = true;
            }
        }

        if (byte_loc == 7 && !is_codewords_parsed(data_loc, ec_loc, params)) {
            if (is_data_parsed(data_loc, params) && !is_ec_parsed(ec_loc, params)) {
                do {
                    block_loc = (block_loc + 1 == params.block_count) ? 0 : block_loc + 1;
                } while (ec_loc[block_loc] == params.blocks[block_loc].err_sz);
                byte = ec[block_loc][ec_loc[block_loc]++] & 0xFF;
                byte_loc = 0;
            } else if (!is_data_parsed(data_loc, params)) {
                do {
                    block_loc = (block_loc + 1 == params.block_count) ? 0 : block_loc + 1;
                } while (data_loc[block_loc] == params.blocks[block_loc].data_sz);
                byte = data[block_loc][data_loc[block_loc]++] & 0xFF;
                byte_loc = 0;
            }
        } else {
            byte_loc++;
        }
    }

    // format
    uint16_t format = get_format(recovery, MASK_6);
    QRcode.modules[(4 * version + 9) * QRcode.width + 8] = default_on;  // Dark module

    // Note: The positions are hardcoded due to awkward skips for the first
    //       batch (top left). So the second batch is copied for consistency
    // top left
    QRcode.modules[8] = (format & 0x1) == 0x1 ? default_on : default_off;
    QRcode.modules[sz + 8] = (format & 0x2) == 0x2 ? default_on : default_off;
    QRcode.modules[2 * sz + 8] = (format & 0x4) == 0x4 ? default_on : default_off;
    QRcode.modules[3 * sz + 8] = (format & 0x8) == 0x8 ? default_on : default_off;
    QRcode.modules[4 * sz + 8] = (format & 0x10) == 0x10 ? default_on : default_off;
    QRcode.modules[5 * sz + 8] = (format & 0x20) == 0x20 ? default_on : default_off;
    QRcode.modules[7 * sz + 8] = (format & 0x40) == 0x40 ? default_on : default_off;
    QRcode.modules[8 * sz + 8] = (format & 0x80) == 0x80 ? default_on : default_off;
    QRcode.modules[8 * sz + 7] = (format & 0x100) == 0x100 ? default_on : default_off;
    QRcode.modules[8 * sz + 5] = (format & 0x200) == 0x200 ? default_on : default_off;
    QRcode.modules[8 * sz + 4] = (format & 0x400) == 0x400 ? default_on : default_off;
    QRcode.modules[8 * sz + 3] = (format & 0x800) == 0x800 ? default_on : default_off;
    QRcode.modules[8 * sz + 2] = (format & 0x1000) == 0x1000 ? default_on : default_off;
    QRcode.modules[8 * sz + 1] = (format & 0x2000) == 0x2000 ? default_on : default_off;
    QRcode.modules[8 * sz] = (format & 0x4000) == 0x4000 ? default_on : default_off;

    // split (bottom left and top right)
    QRcode.modules[9 * sz - 1] = (format & 0x1) == 0x1 ? default_on : default_off;
    QRcode.modules[9 * sz - 2] = (format & 0x2) == 0x2 ? default_on : default_off;
    QRcode.modules[9 * sz - 3] = (format & 0x4) == 0x4 ? default_on : default_off;
    QRcode.modules[9 * sz - 4] = (format & 0x8) == 0x8 ? default_on : default_off;
    QRcode.modules[9 * sz - 5] = (format & 0x10) == 0x10 ? default_on : default_off;
    QRcode.modules[9 * sz - 6] = (format & 0x20) == 0x20 ? default_on : default_off;
    QRcode.modules[9 * sz - 7] = (format & 0x40) == 0x40 ? default_on : default_off;
    QRcode.modules[9 * sz - 8] = (format & 0x80) == 0x80 ? default_on : default_off;
    QRcode.modules[(sz - 7) * sz + 8] = (format & 0x100) == 0x100 ? default_on : default_off;
    QRcode.modules[(sz - 6) * sz + 8] = (format & 0x200) == 0x200 ? default_on : default_off;
    QRcode.modules[(sz - 5) * sz + 8] = (format & 0x400) == 0x400 ? default_on : default_off;
    QRcode.modules[(sz - 4) * sz + 8] = (format & 0x800) == 0x800 ? default_on : default_off;
    QRcode.modules[(sz - 3) * sz + 8] = (format & 0x1000) == 0x1000 ? default_on : default_off;
    QRcode.modules[(sz - 2) * sz + 8] = (format & 0x2000) == 0x2000 ? default_on : default_off;
    QRcode.modules[(sz - 1) * sz + 8] = (format & 0x4000) == 0x4000 ? default_on : default_off;
	
	// version
	if (version >= V7) {
		byte_loc = 0;
		uint32_t version_data = get_version(version);
		for (size_t i = 0; i < 6; ++i) {
			for (size_t j = QRcode.height - 11; j < QRcode.height - 8; ++j) {
				bool bit_val = (version_data & (0x1 << byte_loc)) == (0x1 << byte_loc);
				QRcode.modules[i * sz + j] = bit_val ? default_on : default_off;
				QRcode.modules[j * sz + i] = bit_val ? default_on : default_off;
				byte_loc++;
			}
		}
	}

    for (size_t i = 0; i < params.block_count; ++i) {
        free(data[i]);
        free(ec[i]);
    }
    free(data);
    free(ec);
	free(data_loc);
	free(ec_loc);

    return QRcode;
}

image_t QRcodeToImage(QRcode_t QRcode) {
    size_t width = (QRcode.width + 8) * PIXEL_PER_MODULE;
    size_t height = (QRcode.height + 8) * PIXEL_PER_MODULE;
    image_t image = init_image(width, height);
    pixel_t pixel = WHITE;

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            if (i < 4 * PIXEL_PER_MODULE || j < 4 * PIXEL_PER_MODULE || i >= (QRcode.width + 4) * PIXEL_PER_MODULE ||
                j >= (QRcode.width + 4) * PIXEL_PER_MODULE) {
                pixel = WHITE;
            } else {
                size_t mod_row = i / PIXEL_PER_MODULE - 4;
                size_t mod_col = j / PIXEL_PER_MODULE - 4;

                pixel = QRcode.modules[mod_row * QRcode.width + mod_col].data ? BLACK : WHITE;
            }

            image.pixels[i * width + j] = pixel;
        }
    }

    return image;
}

uint16_t get_format(QR_recovery_t recovery, QR_mask_t mask) {
    uint16_t format_val = (recovery << 3) + mask;
    return ((format_val << 10) + BCH(format_val)) ^ FORMAT_XOR_MASK;
}

uint32_t get_version(QR_version_t version) {
	return (version << 12) + golay(version);
}

inline size_t get_QR_size(QR_version_t QR_version) { return 17 + 4 * QR_version; }

QR_version_params_t get_version_params(QR_version_t QR_version, QR_recovery_t recover) {
    switch (QR_version) {
        case V1:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){1, {{19, 7}}};
                case QR_M:
                    return (QR_version_params_t){1, {{16, 10}}};
                case QR_Q:
                    return (QR_version_params_t){1, {{13, 13}}};
                case QR_H:
                    return (QR_version_params_t){1, {{9, 17}}};
            }
        case V2:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){1, {{34, 10}}};
                case QR_M:
                    return (QR_version_params_t){1, {{28, 16}}};
                case QR_Q:
                    return (QR_version_params_t){1, {{22, 22}}};
                case QR_H:
                    return (QR_version_params_t){1, {{16, 28}}};
            }
        case V3:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){1, {{55, 15}}};
                case QR_M:
                    return (QR_version_params_t){1, {{44, 26}}};
                case QR_Q:
                    return (QR_version_params_t){2, {{17, 18}}};
                case QR_H:
                    return (QR_version_params_t){2, {{13, 22}}};
            }
        case V4:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){1, {{80, 20}}};
                case QR_M:
                    return (QR_version_params_t){2, {{32, 18}, {32, 18}}};
                case QR_Q:
                    return (QR_version_params_t){2, {{24, 26}, {24, 26}}};
                case QR_H:
                    return (QR_version_params_t){4, {{9, 16}, {9, 16}, {9, 16}, {9, 16}}};
            }
        case V5:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){1, {{108, 26}}};
                case QR_M:
                    return (QR_version_params_t){2, {{43, 24}, {43, 24}}};
                case QR_Q:
                    return (QR_version_params_t){4, {{15, 18}, {15, 18}, {16, 18}, {16, 18}}};
                case QR_H:
                    return (QR_version_params_t){4, {{11, 22}, {11, 22}, {12, 22}, {12, 22}}};
            }
        case V6:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){2, {{68, 18}, {68, 18}}};
                case QR_M:
                    return (QR_version_params_t){4, {{27, 16}, {27, 16}, {27, 16}, {27, 16}}};
                case QR_Q:
                    return (QR_version_params_t){4, {{19, 24}, {19, 24}, {19, 24}, {19, 24}}};
                case QR_H:
                    return (QR_version_params_t){4, {{15, 28}, {15, 28}, {15, 28}, {15, 28}}};
            }
        case V7:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){2, {{78, 20}, {78, 20}}};
                case QR_M:
                    return (QR_version_params_t){4, {{31, 18}, {31, 18}, {31, 18}, {31, 18}}};
                case QR_Q:
                    return (QR_version_params_t){6, {{14, 18}, {14, 18}, {15, 18}, {15, 18}, {15, 18}, {15, 18}}};
                case QR_H:
                    return (QR_version_params_t){5, {{13, 26}, {13, 26}, {13, 26}, {13, 26}, {14, 26}}};
            }
        case V8:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){2, {{97, 24}, {97, 24}}};
                case QR_M:
                    return (QR_version_params_t){4, {{38, 22}, {38, 22}, {39, 22}, {39, 22}}};
                case QR_Q:
                    return (QR_version_params_t){6, {{18, 22}, {18, 22}, {18, 22}, {18, 22}, {19, 22}, {19, 22}}};
                case QR_H:
                    return (QR_version_params_t){6, {{14, 26}, {14, 26}, {14, 26}, {14, 26}, {15, 26}, {15, 26}}};
            }
        case V9:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){2, {{116, 30}, {116, 30}}};
                case QR_M:
                    return (QR_version_params_t){5, {{36, 22}, {36, 22}, {36, 22}, {37, 22}, {37, 22}}};
                case QR_Q:
                    return (QR_version_params_t){
                        8, {{16, 20}, {16, 20}, {16, 20}, {16, 20}, {17, 20}, {17, 20}, {17, 20}, {17, 20}}};
                case QR_H:
                    return (QR_version_params_t){
                        8, {{12, 24}, {12, 24}, {12, 24}, {12, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}}};
            }
        case V10:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){4, {{68, 18}, {68, 18}, {69, 18}, {69, 18}}};
                case QR_M:
                    return (QR_version_params_t){5, {{43, 26}, {43, 26}, {43, 26}, {43, 26}, {44, 26}}};
                case QR_Q:
                    return (QR_version_params_t){
                        8, {{19, 24}, {19, 24}, {19, 24}, {19, 24}, {19, 24}, {19, 24}, {20, 24}, {20, 24}}};
                case QR_H:
                    return (QR_version_params_t){
                        8, {{15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {16, 28}, {16, 28}}};
            }
        case V11:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){4, {{81, 20}, {81, 20}, {81, 20}, {81, 20}}};
                case QR_M:
                    return (QR_version_params_t){5, {{50, 30}, {51, 30}, {51, 30}, {51, 30}, {51, 30}}};
                case QR_Q:
                    return (QR_version_params_t){
                        8, {{22, 28}, {22, 28}, {22, 28}, {22, 28}, {23, 28}, {23, 28}, {23, 28}, {23, 28}}};
                case QR_H:
                    return (QR_version_params_t){11,
                                                 {{12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24}}};
            }
        case V12:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){4, {{92, 24}, {92, 24}, {93, 24}, {93, 24}}};
                case QR_M:
                    return (QR_version_params_t){
                        8, {{36, 22}, {36, 22}, {36, 22}, {36, 22}, {36, 22}, {36, 22}, {37, 22}, {37, 22}}};
                case QR_Q:
                    return (QR_version_params_t){10,
                                                 {{20, 26},
                                                  {20, 26},
                                                  {20, 26},
                                                  {20, 26},
                                                  {21, 26},
                                                  {21, 26},
                                                  {21, 26},
                                                  {21, 26},
                                                  {21, 26},
                                                  {21, 26}}};
                case QR_H:
                    return (QR_version_params_t){11,
                                                 {{14, 28},
                                                  {14, 28},
                                                  {14, 28},
                                                  {14, 28},
                                                  {14, 28},
                                                  {14, 28},
                                                  {14, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28}}};
            }
        case V13:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){4, {{107, 26}, {107, 26}, {107, 26}, {107, 26}}};
                case QR_M:
                    return (QR_version_params_t){
                        9, {{37, 22}, {37, 22}, {37, 22}, {37, 22}, {37, 22}, {37, 22}, {37, 22}, {37, 22}, {38, 22}}};
                case QR_Q:
                    return (QR_version_params_t){12,
                                                 {{20, 24},
                                                  {20, 24},
                                                  {20, 24},
                                                  {20, 24},
                                                  {20, 24},
                                                  {20, 24},
                                                  {20, 24},
                                                  {20, 24},
                                                  {21, 24},
                                                  {21, 24},
                                                  {21, 24},
                                                  {21, 24}}};
                case QR_H:
                    return (QR_version_params_t){16,
                                                 {{11, 22},
                                                  {11, 22},
                                                  {11, 22},
                                                  {11, 22},
                                                  {11, 22},
                                                  {11, 22},
                                                  {11, 22},
                                                  {11, 22},
                                                  {11, 22},
                                                  {11, 22},
                                                  {11, 22},
                                                  {11, 22},
                                                  {12, 22},
                                                  {12, 22},
                                                  {12, 22},
                                                  {12, 22}}};
            }
        case V14:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){4, {{115, 30}, {115, 30}, {115, 30}, {116, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        9, {{40, 24}, {40, 24}, {40, 24}, {40, 24}, {41, 24}, {41, 24}, {41, 24}, {41, 24}, {41, 24}}};
                case QR_Q:
                    return (QR_version_params_t){16,
                                                 {{16, 20},
                                                  {16, 20},
                                                  {16, 20},
                                                  {16, 20},
                                                  {16, 20},
                                                  {16, 20},
                                                  {16, 20},
                                                  {16, 20},
                                                  {16, 20},
                                                  {16, 20},
                                                  {16, 20},
                                                  {17, 20},
                                                  {17, 20},
                                                  {17, 20},
                                                  {17, 20},
                                                  {17, 20}}};
                case QR_H:
                    return (QR_version_params_t){16,
                                                 {{12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24}}};
            }
        case V15:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){6, {{87, 22}, {87, 22}, {87, 22}, {87, 22}, {87, 22}, {88, 22}}};
                case QR_M:
                    return (QR_version_params_t){10,
                                                 {{41, 24},
                                                  {41, 24},
                                                  {41, 24},
                                                  {41, 24},
                                                  {41, 24},
                                                  {42, 24},
                                                  {42, 24},
                                                  {42, 24},
                                                  {42, 24},
                                                  {42, 24}}};
                case QR_Q:
                    return (QR_version_params_t){12,
                                                 {{24, 30},
                                                  {24, 30},
                                                  {24, 30},
                                                  {24, 30},
                                                  {24, 30},
                                                  {25, 30},
                                                  {25, 30},
                                                  {25, 30},
                                                  {25, 30},
                                                  {25, 30},
                                                  {25, 30},
                                                  {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){18,
                                                 {{12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {12, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24},
                                                  {13, 24}}};
            }
        case V16:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){6, {{98, 24}, {98, 24}, {98, 24}, {98, 24}, {98, 24}, {99, 24}}};
                case QR_M:
                    return (QR_version_params_t){10,
                                                 {{45, 28},
                                                  {45, 28},
                                                  {45, 28},
                                                  {45, 28},
                                                  {45, 28},
                                                  {45, 28},
                                                  {45, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28}}};
                case QR_Q:
                    return (QR_version_params_t){17,
                                                 {{19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {19, 24},
                                                  {20, 24},
                                                  {20, 24}}};
                case QR_H:
                    return (QR_version_params_t){16,
                                                 {{15, 30},
                                                  {15, 30},
                                                  {15, 30},
                                                  {16, 30},
                                                  {16, 30},
                                                  {16, 30},
                                                  {16, 30},
                                                  {16, 30},
                                                  {16, 30},
                                                  {16, 30},
                                                  {16, 30},
                                                  {16, 30},
                                                  {16, 30},
                                                  {16, 30},
                                                  {16, 30},
                                                  {16, 30}}};
            }
        case V17:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){6, {{107, 28}, {108, 28}, {108, 28}, {108, 28}, {108, 28}, {108, 28}}};
                case QR_M:
                    return (QR_version_params_t){11,
                                                 {{46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {47, 28}}};
                case QR_Q:
                    return (QR_version_params_t){16,
                                                 {{22, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28},
                                                  {23, 28}}};
                case QR_H:
                    return (QR_version_params_t){19,
                                                 {{14, 28},
                                                  {14, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28},
                                                  {15, 28}}};
            }
        case V18:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){6, {{120, 30}, {120, 30}, {120, 30}, {120, 30}, {120, 30}, {121, 30}}};
                case QR_M:
                    return (QR_version_params_t){13,
                                                 {{43, 26},
                                                  {43, 26},
                                                  {43, 26},
                                                  {43, 26},
                                                  {43, 26},
                                                  {43, 26},
                                                  {43, 26},
                                                  {43, 26},
                                                  {43, 26},
                                                  {44, 26},
                                                  {44, 26},
                                                  {44, 26},
                                                  {44, 26}}};
                case QR_Q:
                    return (QR_version_params_t){18,
                                                 {{22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {22, 28},
                                                  {23, 28}}};
                case QR_H:
                    return (QR_version_params_t){
                        21, {{14, 28}, {14, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28},
                             {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28},
                             {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}}};
            }
        case V19:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){
                        7, {{113, 28}, {113, 28}, {113, 28}, {114, 28}, {114, 28}, {114, 28}, {114, 28}}};
                case QR_M:
                    return (QR_version_params_t){14,
                                                 {{44, 26},
                                                  {44, 26},
                                                  {44, 26},
                                                  {45, 26},
                                                  {45, 26},
                                                  {45, 26},
                                                  {45, 26},
                                                  {45, 26},
                                                  {45, 26},
                                                  {45, 26},
                                                  {45, 26},
                                                  {45, 26},
                                                  {45, 26},
                                                  {45, 26}}};
                case QR_Q:
                    return (QR_version_params_t){
                        21, {{21, 26}, {21, 26}, {21, 26}, {21, 26}, {21, 26}, {21, 26}, {21, 26},
                             {21, 26}, {21, 26}, {21, 26}, {21, 26}, {21, 26}, {21, 26}, {21, 26},
                             {21, 26}, {21, 26}, {21, 26}, {22, 26}, {22, 26}, {22, 26}, {22, 26}}};
                case QR_H:
                    return (QR_version_params_t){
                        25, {{13, 26}, {13, 26}, {13, 26}, {13, 26}, {13, 26}, {13, 26}, {13, 26}, {13, 26}, {13, 26},
                             {14, 26}, {14, 26}, {14, 26}, {14, 26}, {14, 26}, {14, 26}, {14, 26}, {14, 26}, {14, 26},
                             {14, 26}, {14, 26}, {14, 26}, {14, 26}, {14, 26}, {14, 26}, {14, 26}}};
            }
        case V20:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){
                        8, {{107, 28}, {107, 28}, {107, 28}, {108, 28}, {108, 28}, {108, 28}, {108, 28}, {108, 28}}};
                case QR_M:
                    return (QR_version_params_t){16,
                                                 {{41, 26},
                                                  {41, 26},
                                                  {41, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26}}};
                case QR_Q:
                    return (QR_version_params_t){20,
                                                 {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                                                  {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                                                  {24, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        25, {{15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28},
                             {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {15, 28}, {16, 28}, {16, 28}, {16, 28},
                             {16, 28}, {16, 28}, {16, 28}, {16, 28}, {16, 28}, {16, 28}, {16, 28}}};
            }
        case V21:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){
                        8, {{116, 28}, {116, 28}, {116, 28}, {116, 28}, {117, 28}, {117, 28}, {117, 28}, {117, 28}}};
                case QR_M:
                    return (QR_version_params_t){17,
                                                 {{42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26},
                                                  {42, 26}}};
                case QR_Q:
                    return (QR_version_params_t){
                        23, {{22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28},
                             {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28},
                             {22, 28}, {23, 28}, {23, 28}, {23, 28}, {23, 28}, {23, 28}, {23, 28}}};
                case QR_H:
                    return (QR_version_params_t){
                        25, {{16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {17, 30}, {17, 30}, {17, 30}, {17, 30}, {17, 30}, {17, 30}}};
            }
        case V22:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){9,
                                                 {{111, 28},
                                                  {111, 28},
                                                  {112, 28},
                                                  {112, 28},
                                                  {112, 28},
                                                  {112, 28},
                                                  {112, 28},
                                                  {112, 28},
                                                  {112, 28}}};
                case QR_M:
                    return (QR_version_params_t){17,
                                                 {{46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28},
                                                  {46, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        23, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        34, {{13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24},
                             {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24},
                             {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24},
                             {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}, {13, 24}}};
            }
        case V23:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){9,
                                                 {{121, 30},
                                                  {121, 30},
                                                  {121, 30},
                                                  {121, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30}}};
                case QR_M:
                    return (QR_version_params_t){18,
                                                 {{47, 28},
                                                  {47, 28},
                                                  {47, 28},
                                                  {47, 28},
                                                  {48, 28},
                                                  {48, 28},
                                                  {48, 28},
                                                  {48, 28},
                                                  {48, 28},
                                                  {48, 28},
                                                  {48, 28},
                                                  {48, 28},
                                                  {48, 28},
                                                  {48, 28},
                                                  {48, 28},
                                                  {48, 28},
                                                  {48, 28},
                                                  {48, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        25, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        30, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}}};
            }
        case V24:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){10,
                                                 {{117, 30},
                                                  {117, 30},
                                                  {117, 30},
                                                  {117, 30},
                                                  {117, 30},
                                                  {117, 30},
                                                  {118, 30},
                                                  {118, 30},
                                                  {118, 30},
                                                  {118, 30}}};
                case QR_M:
                    return (QR_version_params_t){20,
                                                 {{45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {46, 28},
                                                  {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28},
                                                  {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        27, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        32, {{16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {17, 30}, {17, 30}}};
            }
        case V25:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){12,
                                                 {{106, 26},
                                                  {106, 26},
                                                  {106, 26},
                                                  {106, 26},
                                                  {106, 26},
                                                  {106, 26},
                                                  {106, 26},
                                                  {106, 26},
                                                  {107, 26},
                                                  {107, 26},
                                                  {107, 26},
                                                  {107, 26}}};
                case QR_M:
                    return (QR_version_params_t){
                        21, {{47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        29, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        35, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}}};
            }
        case V26:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){12,
                                                 {{114, 28},
                                                  {114, 28},
                                                  {114, 28},
                                                  {114, 28},
                                                  {114, 28},
                                                  {114, 28},
                                                  {114, 28},
                                                  {114, 28},
                                                  {114, 28},
                                                  {114, 28},
                                                  {115, 28},
                                                  {115, 28}}};
                case QR_M:
                    return (QR_version_params_t){
                        23, {{46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28},
                             {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28},
                             {46, 28}, {46, 28}, {46, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        34, {{22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28},
                             {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28},
                             {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28}, {22, 28},
                             {22, 28}, {23, 28}, {23, 28}, {23, 28}, {23, 28}, {23, 28}, {23, 28}}};
                case QR_H:
                    return (QR_version_params_t){
                        37, {{16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {17, 30}, {17, 30}, {17, 30}, {17, 30}}};
            }
        case V27:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){12,
                                                 {{122, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {123, 30},
                                                  {123, 30},
                                                  {123, 30},
                                                  {123, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        25, {{45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28},
                             {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28},
                             {45, 28}, {45, 28}, {45, 28}, {45, 28}, {46, 28}, {46, 28}, {46, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        34, {{23, 30}, {23, 30}, {23, 30}, {23, 30}, {23, 30}, {23, 30}, {23, 30}, {23, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        40, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}}};
            }
        case V28:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){13,
                                                 {{117, 30},
                                                  {117, 30},
                                                  {117, 30},
                                                  {118, 30},
                                                  {118, 30},
                                                  {118, 30},
                                                  {118, 30},
                                                  {118, 30},
                                                  {118, 30},
                                                  {118, 30},
                                                  {118, 30},
                                                  {118, 30},
                                                  {118, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        26, {{45, 28}, {45, 28}, {45, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28},
                             {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28},
                             {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        35, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        42, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}}};
            }
        case V29:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){14,
                                                 {{116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {117, 30},
                                                  {117, 30},
                                                  {117, 30},
                                                  {117, 30},
                                                  {117, 30},
                                                  {117, 30},
                                                  {117, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        28, {{45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28},
                             {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28},
                             {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28}, {45, 28},
                             {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        38, {{23, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        45, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}}};
            }
        case V30:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){15,
                                                 {{115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        29, {{47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        40, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        48, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}}};
            }
        case V31:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){16,
                                                 {{115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        31, {{46, 28}, {46, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        43, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        51, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}}};
            }
        case V32:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){17,
                                                 {{115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        33, {{46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28},
                             {46, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        45, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        54, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}}};
            }
        case V33:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){18,
                                                 {{115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {116, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        35, {{46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28},
                             {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        48, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        57, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}}};
            }
        case V34:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){19,
                                                 {{115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {115, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30},
                                                  {116, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        37, {{46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28},
                             {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        51, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        60, {{16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {17, 30}}};
            }
        case V35:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){19,
                                                 {{121, 30},
                                                  {121, 30},
                                                  {121, 30},
                                                  {121, 30},
                                                  {121, 30},
                                                  {121, 30},
                                                  {121, 30},
                                                  {121, 30},
                                                  {121, 30},
                                                  {121, 30},
                                                  {121, 30},
                                                  {121, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30},
                                                  {122, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        38, {{47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        53, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        63, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}}};
            }
        case V36:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){
                        20, {{121, 30}, {121, 30}, {121, 30}, {121, 30}, {121, 30}, {121, 30}, {122, 30},
                             {122, 30}, {122, 30}, {122, 30}, {122, 30}, {122, 30}, {122, 30}, {122, 30},
                             {122, 30}, {122, 30}, {122, 30}, {122, 30}, {122, 30}, {122, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        40, {{47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {48, 28}, {48, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        56, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        66, {{15, 30}, {15, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}}};
            }
        case V37:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){
                        21, {{122, 30}, {122, 30}, {122, 30}, {122, 30}, {122, 30}, {122, 30}, {122, 30},
                             {122, 30}, {122, 30}, {122, 30}, {122, 30}, {122, 30}, {122, 30}, {122, 30},
                             {122, 30}, {122, 30}, {122, 30}, {123, 30}, {123, 30}, {123, 30}, {123, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        43, {{46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28},
                             {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28},
                             {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28},
                             {46, 28}, {46, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        59, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        70, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}}};
            }
        case V38:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){
                        22, {{122, 30}, {122, 30}, {122, 30}, {122, 30}, {123, 30}, {123, 30}, {123, 30}, {123, 30},
                             {123, 30}, {123, 30}, {123, 30}, {123, 30}, {123, 30}, {123, 30}, {123, 30}, {123, 30},
                             {123, 30}, {123, 30}, {123, 30}, {123, 30}, {123, 30}, {123, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        45, {{46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28}, {46, 28},
                             {46, 28}, {46, 28}, {46, 28}, {46, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        62, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        74, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}}};
            }
        case V39:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){
                        24, {{117, 30}, {117, 30}, {117, 30}, {117, 30}, {117, 30}, {117, 30}, {117, 30}, {117, 30},
                             {117, 30}, {117, 30}, {117, 30}, {117, 30}, {117, 30}, {117, 30}, {117, 30}, {117, 30},
                             {117, 30}, {117, 30}, {117, 30}, {117, 30}, {118, 30}, {118, 30}, {118, 30}, {118, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        47, {{47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        65, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        77, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}}};
            }
        case V40:
            switch (recover) {
                case QR_L:
                    return (QR_version_params_t){
                        25, {{118, 30}, {118, 30}, {118, 30}, {118, 30}, {118, 30}, {118, 30}, {118, 30},
                             {118, 30}, {118, 30}, {118, 30}, {118, 30}, {118, 30}, {118, 30}, {118, 30},
                             {118, 30}, {118, 30}, {118, 30}, {118, 30}, {118, 30}, {119, 30}, {119, 30},
                             {119, 30}, {119, 30}, {119, 30}, {119, 30}}};
                case QR_M:
                    return (QR_version_params_t){
                        49, {{47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28}, {47, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28}, {48, 28},
                             {48, 28}, {48, 28}, {48, 28}, {48, 28}}};
                case QR_Q:
                    return (QR_version_params_t){
                        68, {{24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30},
                             {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {24, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30},
                             {25, 30}, {25, 30}, {25, 30}, {25, 30}, {25, 30}}};
                case QR_H:
                    return (QR_version_params_t){
                        81, {{15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30}, {15, 30},
                             {15, 30}, {15, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30},
                             {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}, {16, 30}}};
            }
        case MV1:
            return (QR_version_params_t){1, {{3, 2}}};
        case MV2:
            if (recover == QR_L) {
                return (QR_version_params_t){1, {{5, 5}}};
            } else {
                return (QR_version_params_t){1, {{4, 6}}};
            }
        case MV3:
            if (recover == QR_L) {
                return (QR_version_params_t){1, {{11, 6}}};
            } else {
                return (QR_version_params_t){1, {{9, 8}}};
            }
        case MV4:
            if (recover == QR_L) {
                return (QR_version_params_t){1, {{16, 8}}};
            } else if (QR_M) {
                return (QR_version_params_t){1, {{14, 10}}};
            } else {
                return (QR_version_params_t){1, {{10, 14}}};
            }
        default:
            return (QR_version_params_t){1, {{19, 7}}};
    }
}
