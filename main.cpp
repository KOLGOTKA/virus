#include "FolderTerrorist.h"

int main(int argc, char **argv) {
    FolderTerrorist::instance()->start(argv[1]);

    return 0;
}
