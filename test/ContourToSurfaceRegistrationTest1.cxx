/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "ContourToSurfaceRegistration.h"

int main( int argc, char * argv [] )
{

  if( argc < 3 )
    {
    std::cerr << "Usage:" << std::endl;
    std::cerr << argv[0] << "input2Dimage  input3Dimage" << std::endl;
    return EXIT_FAILURE;
    }

  ContourToSurfaceRegistration  registration;

  registration.SetInput2DImage( argv[1] );
  registration.SetInput3DImage( argv[2] );

  return EXIT_SUCCESS;
}
