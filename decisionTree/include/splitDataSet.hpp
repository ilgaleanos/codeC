struct Reduced {
        bool value;
        std::string label;
};

// left is false, right is true
inline bool getSide(Node &data, const bool &side) {
        if ( side ) {
                return data.right;
        }
        return data.left;
}

size_t countDataset(Node *dataset, size_t _size, const bool side, const bool value) {
        size_t sizeOut = 0;
        for (size_t i = 0; i < _size; i++) {
                if ( getSide(dataset[i], side) == value ) {
                        sizeOut++;
                }
        }
        return sizeOut;
}

void splitDataSet(Node *dataset, size_t _size, const bool side, const bool value, Reduced *out) {
        for (size_t i = 0, counter = 0; i < _size; i++) {
                if ( getSide(dataset[i], side) == value ) {
                        out[counter] = {value: getSide(dataset[i], side), label: dataset[i].label};
                        counter++;
                }
        }
}
