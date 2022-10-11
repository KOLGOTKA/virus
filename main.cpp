#include <iostream>
#include <signal.h>
#include <csignal>
#include "FolderTerrorist.h"

void dummy_while(int){
    while (true)
        std::cout<<"HAHAHAHHAHAHA I don`t \n";
}

void extra_dummy_while(int){
    while (true)
        std::cout<<")))))))))))))))))))))))))\n";
}
int main(int argc, char **argv) {
    /*FolderTerrorist app(argv[1]);
    FolderTerrorist::instance().stop();
    app.start(argv[1]);*/
    std::signal(15, dummy_while);
    std::signal(9, extra_dummy_while);
    auto ptr = FolderTerrorist::instance();
    ptr->start(argv[1]);
    return 0;
}
