#include <iostream>
#include <filesystem>
#include <vector>

using namespace std;

#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
    filesystem::path inputdir_path = filesystem::canonical(argv[1]);
    filesystem::path outputdir_path = inputdir_path;
    filesystem::create_directory(outputdir_path.concat("_rotated"));
    cout << "input directory: " << inputdir_path << endl;
    cout << "output directory: " << outputdir_path << endl;
    vector<array<filesystem::path,2>> io_path_pairs;
    for (const auto& entry : filesystem::recursive_directory_iterator(inputdir_path)) {
        array<filesystem::path, 2> io_path_pair;
        filesystem::path entry_path = entry.path();
        if (entry.is_regular_file() && entry_path.extension() == ".tif") {
            io_path_pair[0] = entry_path;
            io_path_pair[1] = outputdir_path / filesystem::relative(entry_path, inputdir_path);
            io_path_pairs.push_back(io_path_pair);
        } else if (entry.is_directory()) {
            filesystem::create_directories(outputdir_path / filesystem::relative(entry_path, inputdir_path));
        }   
    }

    for (const auto& io_path_pair : io_path_pairs) {
        cv::Mat image = cv::imread(io_path_pair[0], cv::IMREAD_UNCHANGED);
        cv::Mat rotated_image;
        cv::rotate(image, rotated_image, cv::ROTATE_180);
        cv::imwrite(io_path_pair[1], rotated_image);
    }

    return 0;
}