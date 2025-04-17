


#include <iostream>
#include <memory>
#include <vector>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <cmath>

#include "Curve.h"

#define RND_GEN_DOUBLE_MAX 10000
#define RND_GEN_MAX 5000
#define RND_GEN_DELIMETER 100.f
#define CONTAINER_SIZE 10

static constexpr float my_pi = static_cast<float>(4.f * atan(1.f));

void populateContainer(std::vector<std::shared_ptr<Curve>>& vec, uint16_t size){
	srand(time(0));

	for(int i(0); i < size; ++i){

		float radius_x = (static_cast<float>(rand() % RND_GEN_DOUBLE_MAX)) / RND_GEN_DELIMETER;
		float radius_y = (static_cast<float>(rand() % RND_GEN_DOUBLE_MAX)) / RND_GEN_DELIMETER;
		float x = (static_cast<float>(rand() % RND_GEN_DOUBLE_MAX - RND_GEN_MAX)) / RND_GEN_DELIMETER;
		float y = (static_cast<float>(rand() % RND_GEN_DOUBLE_MAX - RND_GEN_MAX)) / RND_GEN_DELIMETER;
		float step_z = (static_cast<float>(rand() % RND_GEN_DOUBLE_MAX - RND_GEN_MAX)) / RND_GEN_DELIMETER;


		if(i < size/3.f)
			vec.emplace_back(std::shared_ptr<Circle>(new Circle(radius_x, x, y)));
		else if(i < 2.f/3.f * size)
			vec.emplace_back(std::shared_ptr<Elipse>(new Elipse(radius_x, radius_y, x, y)));
		else
			vec.emplace_back(std::shared_ptr<Helix>(new Helix(radius_x, step_z, x, y)));
	}
}

void printCoordinatesByAngle(const std::vector<std::shared_ptr<Curve>>& vec, const float angleRads){
	for (auto& element : vec){
		Point p = element->getPointByAngle(angleRads);
		std::cout << "(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")\n";
	}
}

void printDerivativesByAngle(const std::vector<std::shared_ptr<Curve>>& vec, const float angleRads){
	for (auto& element : vec){
		Point p = element->getDerivativeByAngle(angleRads);
		std::cout << "(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")\n";
	}
}

template <typename T>
void copyFromContainerByType(const std::vector<std::shared_ptr<T>>& from, std::vector<std::shared_ptr<T>>& to, std::string_view& targetType){
	copy_if(from.begin(), from.end(), back_inserter(to), [&targetType](const std::shared_ptr<T>& ptr){
		return typeid(*ptr).name() == targetType;
	});
}

template <typename T>
void printAddressesOfContainersElements(const std::vector<std::shared_ptr<T>>& vec){
	for (auto& address : vec){
		std::cout << address << "\n";
	}
}

void sortCurvesVectorByRadius(std::vector<std::shared_ptr<Curve>>& vec){
	sort(vec.begin(), vec.end(), [](std::shared_ptr<Curve>& ptr1, std::shared_ptr<Curve>& ptr2){
		return ptr1->getRadius().first < ptr2->getRadius().first;
	});
}

void printRadiusOfElements(const std::vector<std::shared_ptr<Curve>>& vec){
	for (auto& element : vec){
		std::cout << element->getRadius().first << "\n";
	}
}

float getRadiusSum(const std::vector<std::shared_ptr<Curve>>& vec){
	return std::accumulate(vec.cbegin(), vec.cend(), 0.f, [](float sum, const std::shared_ptr<Curve>& ptr){
		std::pair<float, float> radiusPair = ptr->getRadius();
		return sum + radiusPair.first + radiusPair.second;
	});
	
}

int main(){
	std::vector<std::shared_ptr<Curve>> curvesVec;
	std::vector<std::shared_ptr<Curve>> circleVec;

	populateContainer(curvesVec, CONTAINER_SIZE);
	std::cout << "\nCurves vector: \n";
	printCoordinatesByAngle(curvesVec, my_pi/4.f);

	std::string_view targetCurveType = typeid(Circle).name();
	copyFromContainerByType<Curve>(curvesVec, circleVec, targetCurveType);

	std::cout << "\nCircle vector: \n";
	printCoordinatesByAngle(circleVec, my_pi/4.f);

	std::cout << "\nCurves: \n";
	printAddressesOfContainersElements(curvesVec);
	std::cout << "\nCircles: \n";
	printAddressesOfContainersElements(circleVec);


	std::cout << "\nUnsorted: \n";
	printRadiusOfElements(circleVec);
	sortCurvesVectorByRadius(circleVec);
	std::cout << "\nSorted: \n";
	printRadiusOfElements(circleVec);

	float radiusSum = getRadiusSum(circleVec);
	std::cout << "\nSum of The radiuses: " << radiusSum << std::endl;
	return 0;
}