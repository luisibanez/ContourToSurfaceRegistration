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
#include "itkTranslationTransform.h"


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
  const unsigned int Dimension = 3;

  typedef itk::EuclideanDistancePointMetric<
    PointSetType, PointSetType>                 MetricType;

  typedef MetricType::TransformType             TransformBaseType;

  typedef itk::LevenbergMarquardtOptimizer      OptimizerType;

  typedef itk::PointSetToPointSetRegistrationMethod<
    PointSetType, PointSetType >                RegistrationType;

  typedef itk::TranslationTransform< double, Dimension >      TransformType;

  RegistrationType::Pointer     registrationMethod;

  typedef itk::ImageFileReader< DistanceMapImageType >  DistanceImageReaderType;

  DistanceImageReaderType::Pointer reader = DistanceImageReaderType::New();
  reader->SetFileName( this->m_Input3DFileName );

  reader->Update();

  reader->GetOutput()->Print( std::cout );

  OptimizerType::Pointer optimizer = OptimizerType::New();

  optimizer->SetUseCostFunctionGradient(false);

  RegistrationType::Pointer registration = RegistrationType::New();

  MetricType::Pointer metric = MetricType::New();

  TransformType::Pointer transform = TransformType::New();

  // Scale the translation components of the Transform in the Optimizer
  OptimizerType::ScalesType scales( transform->GetNumberOfParameters() );
  scales.Fill( 0.01 );


  unsigned long   numberOfIterations =  100;
  double          gradientTolerance  =  1e-5;    // convergence criterion
  double          valueTolerance     =  1e-5;    // convergence criterion
  double          epsilonFunction    =  1e-6;   // convergence criterion


  optimizer->SetScales( scales );
  optimizer->SetNumberOfIterations( numberOfIterations );
  optimizer->SetValueTolerance( valueTolerance );
  optimizer->SetGradientTolerance( gradientTolerance );
  optimizer->SetEpsilonFunction( epsilonFunction );

  // Start from an Identity transform (in a normal case, the user
  // can probably provide a better guess than the identity...
  transform->SetIdentity();

  registration->SetInitialTransformParameters( transform->GetParameters() );

  //------------------------------------------------------
  // Connect all the components required for Registration
  //------------------------------------------------------
  registration->SetMetric(        metric        );
  registration->SetOptimizer(     optimizer     );
  registration->SetTransform(     transform     );
  registration->SetFixedPointSet( this->m_PointSetFrom2DImage );
//  registration->SetMovingPointSet(   movingPointSet   );

}

void
ContourToSurfaceRegistration::
Execute()
{
  this->GeneratePointSetFrom2DImage();
  this->PointSetRegistration();
}

