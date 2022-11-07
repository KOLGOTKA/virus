#pragma once
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <fstream>
#include <csignal>
#include <signal.h>
#include <string>
#include <thread>
#include <vector>
#include <list>
#include <mutex>

class FolderTerrorist {
private:
    static inline FolderTerrorist *imp;
private:
    // Текущая очередь файлов на порчу
    std::list<std::string> _files;
    // Метод обновляющий список файлов на порчу
    void _folderWatcher(std::string path);
    // Метод запускающий порчу файлов по очереди
    void _processFileQueue();

    void _fileTerror(const std::string &filename);
    std::mutex _door;
   FolderTerrorist();
   bool _isStopped = false;

   static void _signalHandler(int signum) {
       std::cout << "Programm catch " << signum << " signal\n";
       FolderTerrorist::instance()->stop();
   };
public:
    void stop();
    void start(std::string path);

    static FolderTerrorist *instance() {
        std::mutex mtx;
        mtx.lock();
        if (imp == nullptr)
            imp = new FolderTerrorist();
        mtx.unlock();
        return imp;
    }

};