
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <fstream>
#include "FolderTerrorist.h"

namespace fs = std::filesystem;

FolderTerrorist::FolderTerrorist() {
    std::cout << "FolderTerrorit has been created\n";
    if (imp == nullptr) imp = this;
    else {
        throw std::runtime_error("Another instance of FD has been created\n");
    }
}

/*FolderTerrorist::FolderTerrorist() {
    namespace fs = std::filesystem;
    if (!fs::exists(fs::path(getFolderName()))){
        throw std::runtime_error("Path " + getFolderName() + " is not exist");////
    }
}*/

FolderTerrorist::FolderTerrorist(const std::string &folderName) {
    namespace fs = std::filesystem;
    if (!fs::exists(fs::path(getFolderName()))) ////////////////////learn
        throw std::runtime_error("Path: " + getFolderName() + "is not exist");
    _threads.push_back(std::thread(&FolderTerrorist::_updateQueue, this));
    _threads.push_back(std::thread(&FolderTerrorist::_releaseQueue, this));
    _threads.push_back(std::thread(&FolderTerrorist::_releaseQueue, this));
    _threads.push_back(std::thread(&FolderTerrorist::_releaseQueue, this));
    _threads.push_back(std::thread(&FolderTerrorist::_releaseQueue, this));
    _threads.push_back(std::thread(&FolderTerrorist::_releaseQueue, this));
    _threads.push_back(std::thread(&FolderTerrorist::_releaseQueue, this));
}

const std::string &FolderTerrorist::getFolderName() const {
    return _folder_name;
}
void FolderTerrorist::start() {
    using namespace std;
    std::cout << "[FolderTerrorist] has be in" << getFolderName();
    for (auto &t : _threads) {
        t.join();
    }
}

std::vector<std::string> FolderTerrorist::_getCurrentFiles() {
    namespace fs = std::filesystem;
    std::cout << "[Scan directory]\n";
    std::vector<std::string> files;
    for (const auto &file : fs::directory_iterator(getFolderName()))
        files.push_back(file.path().c_str());
    return std::vector<std::string>();
}



void FolderTerrorist::_updateQueue() {
    while(true) {
        sleep(5);
        auto files = _getCurrentFiles();
        for (const auto &file : files) {
            if (std::find(_files.begin(), _files.end(), file) == _files.end() && !file.ends_with(".mod")) {
                _door.lock();
                std::cout << "Add queue " << file << "\n";
                _files.push_front(file);
                _door.unlock();
            }
        }
    }

}

void FolderTerrorist::_releaseQueue() {
    std::string filename;
    while(true) {
        _door.lock();
        if (!_files.empty()) {
            filename = _files.back();
            _files.pop_back(); ///learn
        }
        _door.unlock();
        if (fs::exists(fs::path(filename)) && std::filesystem::is_regular_file(fs::path(filename))) {///
            _fileTerror(filename);
        }
        sleep(2);
    }

}

void FolderTerrorist::_fileTerror(const std::string &filename) {
    std::cout << "Terror on file " << filename << "\n";
    std::ifstream ifs(filename, std::ios::binary);
    ifs.seekg(0, std::ios::end);   /////"прыгнем в конец файла" LEARN
    auto filesize = ifs.tellg();   /////"узнаем, сколько байт нам нужно портить" LEARN
    std::vector<uint8_t> data(filesize);
    ifs.seekg(0, std::ios::beg);
    ifs.read(reinterpret_cast<char *>(data.data()), filesize);
    std::transform(data.begin(), data.end(), data.begin(), [](uint8_t byte){ ///std;;transform, lambda LEARN
    return ++byte;
    });
    ifs.close();
    std::remove(filename.c_str()); ///LEARN
    fs::path p = fs::path(filename).parent_path() / fs::path(fs::path(filename).filename().string() + ".mod");
    std::ofstream ofs(p, std::ios::binary);
    ofs.write(reinterpret_cast<const char *>(data.data()), data.size());
}



FolderTerrorist::~FolderTerrorist() {
    std::cout << "FolderTerrorist has been destroyed";
}

void FolderTerrorist::start(const char* path) {
    ///TODO
}

void FolderTerrorist::setFolderName(const std::string &folderName) {
    _folder_name = folderName;
}
