#ifndef RESOURCE_SEARCH_SORT_H
#define RESOURCE_SEARCH_SORT_H

#include "Resource.h"
#include <string>
#include <vector>
using namespace std;

int searchResource(const vector<Resource>& resources, string id);    // It searches for a resource with the given id 

void mergeSortResources(vector<Resource>& resources, int left, int right);  // It sorts the resources by name using merge sort

#endif
