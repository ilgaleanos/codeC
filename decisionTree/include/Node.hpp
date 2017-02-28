class Node {
        private:
                int _numFeatures;
                double *_props;
                std::string _label;
        public:
                Node();
                Node(double *array, const size_t &numFeatures, const std::string label);
                inline void setFeature(const int &index, const double &value);
                inline void setFeatures(double *array);
                inline double getFeature(const int &index);
                inline std::string getLabel();
                inline size_t getNumOfFeatures();
                virtual ~Node();
};

inline void Node::setFeatures(double *array) {
        for (size_t i = _numFeatures; i -->0;) {
                _props[i] = array[i];
        }
}

Node::Node(double *array, const size_t &numFeatures, const std::string label) {
        _numFeatures = numFeatures;
        _props = (double*) malloc ( _numFeatures * 8);
        _label = label;

        setFeatures(array);
}

inline void Node::setFeature(const int &index, const double &value) {
        _props[index] = value;
}

inline double Node::getFeature(const int &index) {
        return _props[index];
}

inline std::string Node::getLabel() {
        return _label;
}

inline size_t Node::getNumOfFeatures() {
        return _numFeatures;
}

Node::~Node() {
	free(_props);
}
