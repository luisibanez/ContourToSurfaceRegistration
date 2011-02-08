#include "itkEuclideanDistancePointMetric.h"
#include "itkLevenbergMarquardtOptimizer.h"
#include "itkPointSetToPointSetRegistrationMethod.h"
#include "itkSignedMaurerDistanceMapImageFilter.h"

class ContourToSurfaceRegistration
{
public:

  ContourToSurfaceRegistration();
  ~ContourToSurfaceRegistration();

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

};
