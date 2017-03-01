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

inline int contain(std::vector<double> &array, const double &value) {
        for (size_t i = 0; i < array.size(); i++) {
                if (array[i] == value) {
                        return i;
                }
        }
        return -1;
}


int chooseBestFeatureToSplit(Node **dataset, size_t _size) {
        size_t numFeatures = dataset[0]->getNumOfFeatures();
        double baseEntropy = Entropy(dataset, _size);
        double bestInfoGain = 0;
        double newEntropy = 0;
        double infoGain = 0;
        int bestFeature = -1;

        std::vector<double> tmp;
        for (size_t i = 0; i < numFeatures; i++) {
                tmp.clear();

                for (size_t j = 0; j < _size; j++) {
                        if ( contain(tmp, dataset[j]->getFeature(i)) != -1) {
                                tmp.push_back(dataset[j]->getFeature(i));
                        }
                }

                newEntropy = 0;
                for (size_t j = 0, L = tmp.size(); j < L; j++) {
                        size_t sizeOut = countDataset(dataset, _size, i, tmp[j] );
                        Node *out[sizeOut];
                        splitDataSet(dataset, _size, i, tmp[j], out);
                        newEntropy += ( sizeOut / _size) * Entropy(out, sizeOut);

                        for (size_t i = 0; i < sizeOut; i++) {
                                delete out[i];
                        }
                }
                infoGain = baseEntropy - newEntropy;
                if (infoGain > bestInfoGain) {
                        bestInfoGain = infoGain;
                        bestFeature = i;
                }
        }

        return bestFeature;
}
