#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main() {
    int n, x;
    std::cin >> n >> x;

    std::vector<int> peserta(x);
    std::map<int, int> freq;

    for (int i = 0; i < x; ++i) {
        std::cin >> peserta[i];
        ++freq[peserta[i]];
    }

    int distrik_menang = -1, max_jumlah = -1;
    for (const auto &p : freq) {
        if (p.second > max_jumlah) {
            max_jumlah = p.second;
            distrik_menang = p.first;
        }
    }

    std::sort(peserta.begin(), peserta.end());
    int distrik_tengah = peserta[(x - 1) / 2];

    std::cout << distrik_menang << " " << distrik_tengah << "\n";

    if (distrik_menang == distrik_tengah) std::cout << "Tidak ada yang menang\n";
    else std::cout << "Distrik " << distrik_menang << " menang\n";

    return 0;
}
