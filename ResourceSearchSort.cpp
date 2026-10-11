#include "ResourceSearchSort.h"
using namespace std;

int searchResources(const vector<Resource>& resources, string id) {    
    for (int i = 0; i < resources.size(); i++) {
        if (resources[i].getID() == id) {                               // It searches each resource until the ID is found
            return i;
        }
    }
    return -1;
}

void mergeResources(vector<Resource>& resources, int left, int mid, int right){    // Combines two sorted halves of the resource list
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    vector<Resource> leftResources(leftSize);          // Used to create temporary lists for both halves of the resources
    vector<Resource> rightResources(rightSize);

    for(int i = 0; i < leftSize; i++) {
        leftResources[i] = resources[left + i];
    }                                                   // Copies the left and right half of the resources
    for (int i = 0; i < rightSize; i++){
        rightResources[i] = resources[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < leftSize && j < rightSize) {                              // Compares the names and merges the resources in order
        if (leftResources[i].getName() <= rightResources[j].getName()) {
            resources[k] = leftResources[i];
            i++;
        } else {
            resources[k] = rightResources[j];
            j++;
        }
        k++;
    }
        while (i < leftSize) {                    // Adds any remaining resources from the left side 
            resources[k] = leftResources[i];
            i++;
            k++;
        }
        while (j < rightSize) {                   // Adds the remaining resources from the right side 
            resources[k] = rightResources[j];
            j++;
            k++;
        }
    }

    void mergeSortResources(vector<Resource>& resources, int left, int right){    //Sorts the resources by name using merge sort
        if (left < right){
            int mid = (left + right) / 2;
            mergeSortResources(resources, left, mid);
            mergeSortResources(resources, mid + 1, right);   
            mergeResources(resources, left, mid, right);
        }
    }
