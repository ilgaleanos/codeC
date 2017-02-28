size_t countDataset(Node **dataset, size_t _size, const size_t axis, const double value) {
        size_t sizeOut = 0;
        for (size_t i = 0; i < _size; i++) {
                if ( dataset[i]->getFeature(axis) == value ) {
                        sizeOut++;
                }
        }
        return sizeOut;
}

void splitDataSet(Node **dataset, size_t _size, const size_t axis, const double value, Node **out) {
        size_t numFeatures = dataset[0]->getNumOfFeatures();
        double tmp[numFeatures];

        for (size_t i = 0, counter = 0; i < _size; i++) {
                if (  dataset[i]->getFeature(axis) == value ) {

                        for (size_t j = 0;  j < axis; j++) {
                                tmp[j] =  dataset[i]->getFeature(j);
                        }

                        for (size_t j = axis+1; j < numFeatures; j++) {
                                tmp[j-1] =  dataset[i]->getFeature(j);
                        }
                        out[counter] = new Node(tmp, numFeatures-1, dataset[i]->getLabel());
                        counter++;
                }
        }
}
