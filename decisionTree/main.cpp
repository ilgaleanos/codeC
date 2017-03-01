/*
*	@author := ilgaleanos@gmail.com*
*/
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <math.h>
#include <vector>

#include <iostream>

#include "./include/Node.hpp"
#include "./include/entropy.hpp"
#include "./include/splitDataSet.hpp"
#include "./include/tree.hpp"


using namespace std;


int main (void) {
        const size_t SIZE = 5;
        const size_t FEAT = 2;


        double values[FEAT];
        Node *dataset[SIZE];

        values[0] = 1;
        values[1] = 1;

        dataset[0] = new Node(values, FEAT, "yes");
        dataset[1] = new Node(values, FEAT, "yes");

        values[0] = 1;
        values[1] = 0;

        dataset[2] = new Node(values, FEAT, "no");

        values[0] = 0;
        values[1] = 1;

        dataset[3] = new Node(values, FEAT, "no");
        dataset[4] = new Node(values, FEAT, "no");

        printf("%0.16f\n", Entropy(dataset, SIZE));



        size_t axis = chooseBestFeatureToSplit(dataset, SIZE);
        double value = 1;
        size_t sizeOut = countDataset(dataset, SIZE, axis, value );
        Node *out[sizeOut];
        splitDataSet(dataset, SIZE, axis, value, out);
        for (size_t i = 0; i < sizeOut; i++) {
                printf("%s\n", out[i]->getLabel().c_str() );
        }

        Tree *mDemo  = new Tree(*dataset, SIZE);
        delete mDemo;
        for (size_t i = 0; i < SIZE; i++) {
                delete dataset[i];
        }
        for (size_t i = 0; i < sizeOut; i++) {
                delete out[i];
        }

        return 0;
}
