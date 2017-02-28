double Entropy( Node **dataset, size_t _size) {
        std::map < std::string, int > labelCounts;
        std::map < std::string, int >::iterator iterator;

        std::string currentLabel;
        for (size_t i = 0; i < _size; i++) {
                currentLabel = dataset[i]->getLabel();
                iterator = labelCounts.find(currentLabel);
                if ( iterator == labelCounts.end() ) {
                        labelCounts[currentLabel] = 1;
                } else {
                        labelCounts[currentLabel] = labelCounts[currentLabel] + 1;
                }
        }

        double prob = 0;
        double shannonEnt = 0;
        for(iterator = labelCounts.begin(); iterator != labelCounts.end(); iterator++) {
                prob = iterator->second / (double)_size;
                shannonEnt -= prob * log2(prob);
        }

        return shannonEnt;
}
