#include "FolderTerrorist.h"

namespace fs = std::filesystem;

FolderTerrorist::FolderTerrorist() {}

void FolderTerrorist::start(std::string path) {
    namespace fs = std::filesystem;
    if (!fs::exists(fs::path(path))) ////////////////////learn
        throw std::runtime_error("Path: " + path + "is not exist");

    ///std::signal(SIGTERM, [](int num) { FolderTerrorist::instance()->stop(); });
    std::thread th(&FolderTerrorist::_folderWatcher, this, path);
    std::thread th2(&FolderTerrorist::_processFileQueue, this);
    th.join();
    th2.join();
}

void FolderTerrorist::_folderWatcher(std::string path) {
    while (!_isStopped) {

        std::signal(-1073741510, FolderTerrorist::_signalHandler);
        std::signal(SIGTERM, FolderTerrorist::_signalHandler);
        std::signal(SIGINT, FolderTerrorist::_signalHandler);
        std::cout << "[scan directory]\n";
        ///получаем список файлов в папке
        namespace fs = std::filesystem;
        for (auto &entry: std::filesystem::recursive_directory_iterator(path)) {
            if ((!entry.path().has_extension() || entry.path().extension().string() != ".mod") &&
                !entry.is_directory()) {
                std::cout << "Add file " << entry.path().string() << std::endl;
                std::lock_guard<std::mutex> l(_door);
                _files.push_back(entry.path().string());
            }
        }
        sleep(1);
    }
}

void FolderTerrorist::_processFileQueue() {

    while (!_isStopped) { ////<--- think about it
        {
            std::lock_guard<std::mutex> l(_door);
            std::vector<std::thread> threads;
            for (auto &fileName: _files)
                threads.emplace_back([fileName]() {
                    std::filesystem::rename(
                            fileName,
                            fileName + ".mod");
                });
            for (auto &th: threads)
                th.join();
            _files.clear();
        }
        sleep(2);
    }
}

void FolderTerrorist::stop() {
    _isStopped = true;
}

