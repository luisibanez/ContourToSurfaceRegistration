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

#include "itkBinaryMaskToNarrowBandPointSetFilter.h"
#include "itkEuclideanDistancePointMetric.h"
#include "itkLevenbergMarquardtOptimizer.h"
#include "itkPointSetToPointSetRegistrationMethod.h"
#include "itkSignedMaurerDistanceMapImageFilter.h"
#include "itkImageFileReader.h"

ContourToSurfaceRegistration::
ContourToSurfaceRegistration()
{

}


ContourToSurfaceRegistration::
~ContourToSurfaceRegistration()
{

}


void
ContourToSurfaceRegistration::
SetInput2DImage( const char * filename )
{
  this->m_Input2DFileName = filename;
}


void
ContourToSurfaceRegistration::
SetInput3DImage( const char * filename )
{
  this->m_Input3DFileName = filename;
}


void
ContourToSurfaceRegistration::
GeneratePointSetFrom2DImage()
{
  typedef itk::BinaryMaskToNarrowBandPointSetFilter< ImageMaskType, PointSetType >  MaskToPointSetFilterType;
  MaskToPointSetFilterType::Pointer  maskToPointSetFilter = MaskToPointSetFilterType::New();

  typedef itk::ImageFileReader< ImageMaskType >  SliceImageReaderType;

  SliceImageReaderType::Pointer reader = SliceImageReaderType::New();
  reader->SetFileName( this->m_Input2DFileName );

  maskToPointSetFilter->SetInput( reader->GetOutput() );

  maskToPointSetFilter->Update();

  this->m_PointSetFrom2DImage = maskToPointSetFilter->GetOutput();

  this->m_PointSetFrom2DImage->Print( std::cout );
}


void
ContourToSurfaceRegistration::
PointSetRegistration()
{
  typedef itk::EuclideanDistancePointMetric<
    PointSetType, PointSetType>                 MetricType;

  typedef MetricType::TransformType             TransformBaseType;

  typedef itk::LevenbergMarquardtOptimizer      OptimizerType;

  typedef itk::PointSetToPointSetRegistrationMethod<
    PointSetType, PointSetType >                RegistrationType;

  RegistrationType::Pointer     registrationMethod;

  typedef itk::ImageFileReader< DistanceMapImageType >  DistanceImageReaderType;

  DistanceImageReaderType::Pointer reader = DistanceImageReaderType::New();
  reader->SetFileName( this->m_Input3DFileName );

  reader->Update();

  reader->GetOutput()->Print( std::cout );
}

void
ContourToSurfaceRegistration::
Execute()
{
  this->GeneratePointSetFrom2DImage();
  this->PointSetRegistration();
}

