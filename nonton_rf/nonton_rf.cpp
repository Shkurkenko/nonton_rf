#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>

struct Product {
    std::string id;
    std::string name;
};

class ProductsImpl {

public:
    std::unordered_map<std::string, std::string> bucket;

    bool addProduct(Product product) {
        if(bucket.find(product.id) == bucket.end()) {
            bucket.insert(std::make_pair(product.id, product.name));
            return true;
        }
        return false;
    }

    bool deleteProduct(Product product) {
        if(bucket.find(product.id) != bucket.end()) {
            bucket.erase(product.id);
            return true;
        }
        return false;
    }

    std::string getName(std::string id) {
        if(bucket.find(id) != bucket.end()) {
            return bucket[id];
        }
        return "";
    }

    std::vector<std::string> findByName(std::string name) {
        std::vector<std::string> names;
        for(auto &product: bucket) {
            if(product.second == name) {
                names.push_back(product.first);
            }
        }
        return names;
    }    
};

int main() {

    // Example

    Product prod1{ "12345x", "value1" };
    Product prod4{ "12345678x", "value1" };
    Product prod2{ "123456x", "value2" };
    Product prod3{ "1234567x", "value3" };


    ProductsImpl products;

    std::cout << "addProduct(Product prod) method demo:" << "\n";

    products.addProduct(prod1);
    products.addProduct(prod2);
    products.addProduct(prod3);
    products.addProduct(prod4);

    // Add prod3 twice to test
    products.addProduct(prod3);

    for (auto &product: products.bucket) {
        std::cout << '\t' << product.first << " : " << product.second << '\n';
    }
    
    std::cout << "getName(string id) method demo:" << '\n';

    std::cout << '\t' << products.getName("12345x") << '\n';
    std::cout << '\t' << products.getName("123456x") << '\n';
    std::cout << '\t' << products.getName("1234567x") << '\n';
    
    // failed test
    std::cout << '\t' << "Non exist id: " << products.getName("non exist id") << '\n';

    std::cout << "findByName(string name) method demo: " << '\n';

    auto found = products.findByName("value1");
    
    for (auto &el : found) {
        std::cout << '\t' << el << '\n';
    }
    
    std::cout << "deleteProduct(string id) method demo:" << '\n';

    products.deleteProduct(prod1);
    products.deleteProduct(prod2);
    products.deleteProduct(prod3);

	for (auto &product: products.bucket) {
        std::cout << '\t' << product.first << " : " << product.second << '\n';
    }

    return 0;
}