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

#include "itkEuclideanDistancePointMetric.h"
#include "itkLevenbergMarquardtOptimizer.h"
#include "itkPointSetToPointSetRegistrationMethod.h"
#include "itkSignedMaurerDistanceMapImageFilter.h"

class ContourToSurfaceRegistration
{
public:

  ContourToSurfaceRegistration();
  ~ContourToSurfaceRegistration();

  void SetInput2DImage( const char * filename );
  void SetInput3DImage( const char * filename );

private:

  typedef itk::PointSet< double, 3 >            PointSetType;

  typedef PointSetType::PointType               PointType;
  typedef PointSetType::PointsContainer         PointsContainer;

  typedef itk::EuclideanDistancePointMetric<
    PointSetType, PointSetType>                 MetricType;

  typedef MetricType::TransformType             TransformBaseType;

  typedef itk::LevenbergMarquardtOptimizer      OptimizerType;

  typedef itk::PointSetToPointSetRegistrationMethod<
    PointSetType, PointSetType >                RegistrationType;

  RegistrationType::Pointer     m_RegistrationMethod;

private:

  std::string      m_Input2DFileName;
  std::string      m_Input3DFileName;

};
