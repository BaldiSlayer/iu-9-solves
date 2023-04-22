#include <iostream>
#include <unordered_map>

using namespace std;

template<typename T>
class SparseArray {
public:
    SparseArray(const T& defaultValue = T()) : defaultValue(defaultValue) {}

    T& operator[](const int index) {
        if (map.find(index) == map.end()) {
            map[index] = defaultValue;
        }
        return map[index];
    }

    SparseArray<T> operator()(const int start, const int end) const {
        SparseArray<T> subarray(defaultValue);
        for (const auto& [index, value] : map) {
            if (index >= start && index < end) {
                subarray[index] = value;
            }
        }
        return subarray;
    }

    bool operator==(const SparseArray<T>& other) const {
        if (this->map.size() != other.map.size()) {
            return false;
        }
        for (const auto& [index, value] : map) {
            if (other.map.find(index) == other.map.end() || other.map.find(index)->second != value) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const SparseArray<T>& other) const {
        return !(*this == other);
    }

private:
    std::unordered_map<int, T> map;
    T defaultValue;
};

int main() {
    SparseArray<int> arr(0);

    arr[2] = 2;
    arr[4] = 4;
    arr[6] = 6;
    arr[8] = 8;

    cout << arr[8] << "\n";

    SparseArray<int> subarray = arr(2, 7);

    for (int i = 2; i < 7; i++) {
        std::cout << subarray[i] << " ";
    }
    cout << "\n";

    SparseArray<int> brr(0);

    brr[2] = 2;
    brr[4] = 4;
    brr[6] = 6;
    brr[8] = 8;

    cout << (brr == arr) << "\n";

    brr[7] = 7;

    cout << (brr == arr) << "\n";
    cout << (brr != arr);

    return 0;
}