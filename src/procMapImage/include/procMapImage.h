#pragma once

#include "../../appStateMachine/include/appStateMachine.h"
#include <opencv2/core.hpp>

typedef struct 
{
    float meters_per_cell;
    uint32_t map_width;
    uint32_t map_height;
    std::pair<uint32_t, uint32_t> map_origin;
    cv::Mat map_image;
} mapData_t;

class ProcMapImage {
    public:
        /**
         * @brief class constructor.
         * @param raw_map the raw map matrix read from the image file in question
        */
        ProcMapImage(cv::Mat raw_map);

        /**
         * @brief the function that manages running all the stages of map
         * generation. It advances the internal state machine when each stage
         * is completed successfully.
         * @return a mapData_t struct instance with collected map metadata.
        */
        mapData_t RunImageProc();

        /**
         * @brief the class context onClick callback function. This function
         * will address click events in the context of the current state machine
         * state.
         * @param x the x location of the click.
         * @param y the y location of the click.
        */
        void ClickCallback(int x, int y);
    private:
        // the internal state machine for tracking
        // user interaction progress
        ApplicationStateMachine _state_machine;

        // various internal class members for storing
        // intermediate images during map processing.
        float _scale_meters_per_pixel;
        cv::Mat _raw_map;
        cv::Mat _raw_map_draw_copy;
        cv::Mat _cropped_map;
        cv::Mat _text_removed_map;
        cv::Mat _doors_removed_map;

        // boundary points and flag for crop operation
        std::vector<std::pair<int, int>> _boundary_points;
        bool _got_boundary;

        /**
         * @brief function to manage map boundary selection. This function
         * will prompt the user to select the boundary of the map in the image,
         * perform the crop operation and ask for confirmation.
        */
        bool SelectMapBoundary();

        /**
         * @brief function to select a known scale. This function will prompt the user
         * to select a known distance in the map. This distance in pixels and the
         * provided distance in meters will be used to generate a pixel/m ratio.
        */
        bool SelectKnownScale();

        /**
         * @brief function to select text locations for deletions. This function 
         * will prompt the user to select locations within the image with text.
         * This text will be extracted using OCR and remove from the image.
        */
        bool SelectText();

        /**
         * @brief function to select doors in the image. This door template
         * will be used to find other similar doors within the image, and remove them.
        */
        bool SelectDoors();

        /**
         * @brief a function to generate map metadata based on responses 
         * and input from the user stored as class members.
         * @return a mapData_t struct instance with collected map metadata.
        */
        mapData_t GenerateMapData();
};