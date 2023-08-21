//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
// 
// MIT License
// 
// Copyright(c) 2023 Gerald Filimonov
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <filesystem>
#include "../../util/logger.h"
#include "mnistdatasetreader.h"
#include "mnistdataset.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  CTORs/DTORs
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



MNISTDataSetReader::MNISTDataSetReader() {}
MNISTDataSetReader::~MNISTDataSetReader() {}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function loadMNISTData()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool MNISTDataSetReader::loadMNISTData(MNISTDataSet &mnistdataset, std::string imagefile, std::string labelfile) {
	
	
	std::ifstream file;



	//****************************************************************************************************
	//****************************************************************************************************
	//*                                                                                                  *
	//*   Load the images                                                                                *
	//*                                                                                                  *
	//****************************************************************************************************
	//****************************************************************************************************

	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "Reading in mnist image data: " + imagefile);
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");


	//does the file exist?
	if (std::filesystem::exists(imagefile))
	{
		//open the source file
		file.open(imagefile, std::ios::in | std::ios::binary);

		//did the file open sucessfully?
		if (file.is_open()) {

			//get the file size, internet cant agree on whether this is legit or not, seems to be working so far
			file.seekg(0, std::ios::end);
			unsigned long filesize = (unsigned long)file.tellg();
			file.seekg(0, std::ios::beg);

			uint32_t magic_number;   // should be 0x00000803
			uint32_t num_images;     // number of images in the file
			uint32_t num_rows;       // number of rows in each image
			uint32_t num_columns;    // number of columns in each image


			file.read(reinterpret_cast<char*>(&magic_number), sizeof(magic_number));
			magic_number = swap_endian(magic_number); // swap endianness if necessary

			file.read(reinterpret_cast<char*>(&num_images), sizeof(num_images));
			num_images = swap_endian(num_images); // swap endianness if necessary

			file.read(reinterpret_cast<char*>(&num_rows), sizeof(num_rows));
			num_rows = swap_endian(num_rows); // swap endianness if necessary

			file.read(reinterpret_cast<char*>(&num_columns), sizeof(num_columns));
			num_columns = swap_endian(num_columns); // swap endianness if necessary

			size_t num_pixels = num_rows * num_columns;

			for (unsigned int i = 0; i < num_images; i++) {


				std::vector<uint8_t> tempdata;
				tempdata.resize(num_pixels);

				MNISTImage image;				
				image.pixels.resize(num_pixels);

				file.read(reinterpret_cast<char*>(&tempdata[0]), num_pixels);
				for (unsigned int pixel = 0; pixel < num_pixels; pixel++) {
					image.pixels[pixel] = (double)tempdata[pixel] / 255.0;
				}

				Logger::Append(Logger::LogLevel::LOGLEVEL_DEBUG, "Loaded Image: " + std::to_string(i));
				mnistdataset.images.push_back(image);
			}

			file.close();
		}
		else {
			//TODO: file didnt open error out
			Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "ERROR: Failed to open file" + imagefile);
			return false;
		}

	}
	else {
		//TODO: file didnt exist error out
		Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "ERROR: File does not exist" + imagefile);
		return false;
	}

	//****************************************************************************************************
	//****************************************************************************************************
	//*                                                                                                  *
	//*   Load the Labels                                                                                *
	//*                                                                                                  *
	//****************************************************************************************************
	//****************************************************************************************************


	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "Reading in mnist label data: " + labelfile);
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");
	Logger::Append(Logger::LogLevel::LOGLEVEL_INFO, "");


	//does the file exist?
	if (std::filesystem::exists(labelfile))
	{
		//open the source file
		file.open(labelfile, std::ios::in | std::ios::binary);

		//did the file open sucessfully?
		if (file.is_open()) {

			//get the file size, internet cant agree on whether this is legit or not, seems to be working so far
			file.seekg(0, std::ios::end);
			unsigned long filesize = (unsigned long)file.tellg();
			file.seekg(0, std::ios::beg);

			uint32_t magic_number;   // should be 0x00000803
			uint32_t num_labels;     // number of images in the file

			file.read(reinterpret_cast<char*>(&magic_number), sizeof(magic_number));
			magic_number = swap_endian(magic_number); // swap endianness if necessary

			file.read(reinterpret_cast<char*>(&num_labels), sizeof(num_labels));
			num_labels = swap_endian(num_labels); // swap endianness if necessary

			for (unsigned int i = 0; i < num_labels; i++) {

				char label;

				file.read(&label, 1);
				Logger::Append(Logger::LogLevel::LOGLEVEL_DEBUG, "Loaded Label: " + std::to_string(i));

				mnistdataset.images[i].label = label;
			}

			file.close();
		}
		else {
			//TODO: file didnt open error out
			Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "ERROR: Failed to open file" + labelfile);
			return false;
		}

	}
	else {
		//TODO: file didnt exist error out
		Logger::Append(Logger::LogLevel::LOGLEVEL_ERROR, "ERROR: File does not exist" + labelfile);
		return false;
	}


	return true;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function swap_endian()
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


uint32_t MNISTDataSetReader::swap_endian(uint32_t x) {
	x = (x >> 16) | (x << 16);
	return ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
}
