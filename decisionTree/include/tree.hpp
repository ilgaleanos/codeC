class Tree {
        private:
                size_t _size;
                Node *_datos;
        public:
                Tree(Node* datos, const size_t size) ;
};

Tree::Tree(Node* datos, const size_t size) {
        _size = size;
        _datos = datos;
}
