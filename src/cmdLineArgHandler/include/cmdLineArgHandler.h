#pragma once

#include <filesystem>
#include <iostream>
#include <map>
#include <opencv2/core.hpp>

class CommandLineArgHandler {
public:
  /**
   * @brief prints the application usage menu to stdout
   */
  void printUsageMenu();

  /**
   * @brief parses command line arguments from user.
   * @param argv the provided filepath from the user
   * @return a map of filenames and associated cv::Mat objects
   */
  std::map<std::string, cv::Mat> parseCommandLineArgs(char **argv);

private:
  /**
   * @brief function to determine if a provided path to image
   * has an extension corresponding to an acceptable image format.
   * @param provided_path the full path to the image under test.
   * @return true if valid format, false otherwise.
   */
  bool isValidFormat(std::filesystem::path provided_path);

  std::vector<std::filesystem::path> acceptable_formats = {
      std::filesystem::path(".png"),  std::filesystem::path(".jpg"),
      std::filesystem::path(".jpeg"), std::filesystem::path(".bmp"),
      std::filesystem::path(".gif"),  std::filesystem::path(".pbm"),
      std::filesystem::path(".pgm"),  std::filesystem::path(".ppm"),
      std::filesystem::path(".pnm")};
};