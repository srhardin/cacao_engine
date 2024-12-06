/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: MeshLoader.cpp
Purpose: Load and display a mesh with basic lighting
Language: C++ / compiled with Visual Studio 2017
Platform: Windows 10 using Windows 8.1 SDK
Project: s.hardin_CS300_2
Author: Samuel Hardin / s.hardin
Creation date: 9-27-17
End Header --------------------------------------------------------*/
#include "Precompiled.h"
#include "framework/Debug.h"
#include "framework/Utilities.h"
#include "graphics/MeshLoader.h"
#include "graphics/TriangleMesh.h"
#include <string>

namespace Graphics
{
  std::shared_ptr<TriangleMesh> MeshLoader::LoadMesh(std::string const &objFile)
  {
      std::stringstream stream;
      stream << ASSET_PATH << "models/" << objFile;
      std::ifstream input = std::ifstream(stream.str());
      if (!input.good())
      {
          std::cerr << "Cannot load mesh: assets/models/%s" << std::endl;
          return NULL;
      }

      std::shared_ptr<TriangleMesh> newMesh = std::make_shared<TriangleMesh>();
      std::string in = ReadToString(input);
      stream = std::stringstream(in);

      std::vector<std::string> perLine;
      std::string line;

      f32 f1, f2, f3;
      u32 u1, u2, u3;

      while (!stream.eof())
      {
          getline(stream, line);
          if (line[0] == 'v')
          {
              DelimitString(line, perLine);
              f1 = atof(perLine[1].c_str());
              f2 = atof(perLine[2].c_str());
              f3 = atof(perLine[3].c_str());

              newMesh->AddVertex(f1, f2, f3);
          }
          else if (line[0] == 'f')
          {
              DelimitString(line, perLine);
              u1 = atoi(perLine[1].c_str()) - 1;
              u2 = atoi(perLine[2].c_str()) - 1;
              u3 = atoi(perLine[3].c_str()) - 1;

              newMesh->AddTriangle(u1, u2, u3);
          }

          perLine.clear();
          line.clear();
      }

      newMesh->Preprocess();
      return newMesh;
  }

  void MeshLoader::DelimitString(std::string & inStr, std::vector<std::string>& outStr)
  {
      size_t pos = 0;
      std::string subStr;
      while ((pos = inStr.find(' ')) != std::string::npos)
      {
          subStr = inStr.substr(0, pos);
          outStr.push_back(subStr);
          inStr.erase(0, pos + 1);
      }
      subStr = inStr.substr(0, pos);
      outStr.push_back(subStr);
  }

  std::string MeshLoader::ReadToString(std::ifstream& in, std::allocator<std::string> alloc)
  {
      std::ostringstream ss(std::string(std::move(alloc)));

      if (!(ss << in.rdbuf()))
          throw std::ios_base::failure{ "error reading to string" };

      return ss.str();
  }
}
