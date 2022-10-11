#pragma once
#include <string>
#include <thread>
#include <vector>
#include <list>
#include <mutex>

class FolderTerrorist {
private:
    static inline FolderTerrorist *imp;
    // Путь до папки в которой будет устроен терроризм
    std::string _folder_name;
public:
    void setFolderName(const std::string &folderName);

public:
    const std::string &getFolderName() const;

private:
    // Массив потоков, в котором будут лежать треды, творящие нечто
    std::vector<std::thread> _threads;
    // Текущая очередь файлов на порчу
    std::list<std::string> _files;
    // Получить список текущих файлов в папке
    std::vector<std::string> _getCurrentFiles();
    // Метод обновляющий список файлов на порчу
    void _updateQueue();
    // Метод запускающий порчу файлов по очереди
    void _releaseQueue();

    void _fileTerror(const std::string &filename);
    // Метод отслеживаюший сигнал
    void _signalHandler(); //TODO
    std::mutex _door;
public:
   FolderTerrorist(const std::string &folderName); ////

    FolderTerrorist();

    static FolderTerrorist *instance() {
        if (imp == nullptr)
            imp = new FolderTerrorist;
        return imp;
    }
    virtual ~FolderTerrorist();

    void start();
    void start(const char* path);
    void stop();

    static void myHandler(int signum) {
        ///TODO
    }

};