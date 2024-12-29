#include <iostream>
#include <vector>

using namespace std;

void fusion(vector<int> &vect, int gauche, int mid, int droite)
{
    int taille_gauche = mid - gauche + 1;
    int taille_droite = droite - mid;
    vector<int> tmp_gauche, tmp_droite;

    for (int i = 0; i < taille_gauche; i++)
    {
        tmp_gauche.push_back(vect[i + gauche]);
    }

    for (int j = 0; j < taille_droite; j++)
    {
        tmp_droite.push_back(vect[mid + j + 1]);
    }

    int i = 0, j = 0, k = gauche;

    while (i < taille_gauche && j < taille_droite)
    {
        if (tmp_gauche[i] <= tmp_droite[j])
        {
            vect[k] = tmp_gauche[i];
            i++;
        }
        else
        {
            vect[k] = tmp_droite[j];
            j++;
        }
        k++;
    }

    while (i < taille_gauche)
    {
        vect[k++] = tmp_gauche[i++];
    }

    while (j < taille_droite)
    {
        vect[k++] = tmp_droite[j++];
    }
}

void tri_fusion(vector<int> &vect, int gauche, int droite)
{
    if (gauche < droite)
    {
        int mid = gauche + (droite - gauche) / 2;
        tri_fusion(vect, gauche, mid);
        tri_fusion(vect, mid + 1, droite);

        fusion(vect, gauche, mid, droite);
    }
}
int main()
{
    vector<int> arr = {38, 27, 43, 3, 9, 82, 10};

    cout << "Liste originale : ";
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    tri_fusion(arr, 0, arr.size() - 1);

    cout << "Liste triée : ";
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}