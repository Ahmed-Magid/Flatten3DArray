#include <iostream>

template<class T>
class My3DArray {
private:
    int width;
    int height;
    int depth;
    T*** threeDArray;

    void initializeArray() {
        /**
         * Initializes the array dynamically with the given width, height and depth.
         */

        threeDArray = new T**[width];
        for (int i = 0; i < width; i++) {
            threeDArray[i] = new T*[height];
            for (int j = 0; j < height; j++)
                threeDArray[i][j] = new T[depth];
        }
    }

    int hash(int x, int y, int z) {
        /**
         * Converts the indices x, y and z from a 3D array to an index that can fit in a 1D array giving each element in the 3D array a place in the 1D array in the same given order.
         * @param x Index x
         * @param y Index y
         * @param z Index z
         * @returns The corresponding single unique index to the given indices.
         */

        return x * height * depth + y * depth + z;
    }



public:
    My3DArray(int width, int height, int depth) {
        /**
         * A constructor that sets dimensions variables
         * @param width Width of the array.
         * @param height Height of the array.
         * @param depth Depth of the array.
         */

        this->width = width;
        this->height = height;
        this->depth = depth;
        initializeArray();
    }

    T* to1DArray() {
        /**
         * Converts a 3D array to a 1D array by hashing each i, j, k index using the hash function and use the resulting index to set the 1D array.
         * @returns The 1D array after assigning all of its elements.
         */

        T* array = new T[oneDArraySize()];
        for (int i = 0; i < width; i++)
            for (int j = 0; j < height; j++)
                for (int k = 0; k < depth; k++)
                    array[hash(i, j, k)] = threeDArray[i][j][k];
        return array;
    }

    int oneDArraySize() {
        /**
         * @returns The resulting 1D array size corresponding to the chosen hash function.
         */

        return width * height * depth;
    }

    void setAt(int x, int y, int z, int value) {
        /**
         * Sets the element with given indices in the 3D array with the given value.
         * @param x Index x
         * @param y Index y
         * @param z Index z
         * @param value The value to be set.
         */

        threeDArray[x][y][z] = value;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    int getDepth() const {
        return depth;
    }
};

int main() {
    int width;
    int height;
    int depth;
    int value;
    std::cout << "Enter the array's width: ";
    std::cin >> width;
    std::cout << "Enter the array's height: ";
    std::cin >> height;
    std::cout << "Enter the array's depth: ";
    std::cin >> depth;
    My3DArray<int> my3DArray(width, height, depth);
    std::cout << "Enter array elements:\n";
    for (int i = 0; i < my3DArray.getWidth(); i++) {
        for (int j = 0; j < my3DArray.getHeight(); j++) {
            for (int k = 0; k < my3DArray.getDepth(); k++) {
                std::cin >> value;
                my3DArray.setAt(i, j, k, value);
            }
        }
    }
    int* oneDArray = my3DArray.to1DArray();
    std::cout << "Flattened 1D array is: ";
    for (int i = 0; i < my3DArray.oneDArraySize(); i++)
        std::cout << oneDArray[i] << ' ';
    return 0;
}
