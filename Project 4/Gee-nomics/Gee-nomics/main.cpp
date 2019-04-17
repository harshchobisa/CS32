
#include "Trie.h"
#include <iostream>
#include <fstream> // needed to open files
#include <string>
#include <vector>
#include "provided.h"
class Genome;
class GenomeMatcher;
using namespace std;

int main()
{
    cout << "--- testing findGenomesWithTHISDNA with spec tests----" << endl;
    
    int i = 1;
    cout << "****TEST " << i << "*****" << endl;
    GenomeMatcher* test1 = new GenomeMatcher(4);
    test1->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    test1->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    test1->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    vector<DNAMatch> matches1;
    bool result;
    result = test1->findGenomesWithThisDNA("GAAG", 4, true, matches1);
    
    if (result) {
        cout << "result is true" << endl;
    }
    else {
        cout << "result is false" << endl;
    }
    cout << "matches are: " << endl;
    for (int i = 0; i != matches1.size(); i++) {
        cout << "genome: " << matches1[i].genomeName << " length: " << matches1[i].length << " position: " << matches1[i].position << endl;
    }
    i++;
    delete test1;
    
    cout << "****TEST " << i << "*****" << endl;
    GenomeMatcher* test2 = new GenomeMatcher(4);
    test2->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    test2->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    test2->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    vector<DNAMatch> matches2;
    bool result2;
    result2 = test2->findGenomesWithThisDNA("GAATAC", 4, true, matches2);
    
    if (result2) {
        cout << "result is true" << endl;
    }
    else {
        cout << "result is false" << endl;
    }
    cout << "matches are: " << endl;
    for (int i = 0; i != matches2.size(); i++) {
        cout << "genome: " << matches2[i].genomeName << " length: " << matches2[i].length << " position: " << matches2[i].position << endl;
    }
    i++;
    delete test2;
    
    cout << "****TEST " << i << "*****" << endl;
    GenomeMatcher* test3 = new GenomeMatcher(4);
    test3->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    test3->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    test3->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    vector<DNAMatch> matches3;
    bool result3;
    result3 = test3->findGenomesWithThisDNA("GAATAC", 6, true, matches3);
    
    if (result3) {
        cout << "result is true" << endl;
    }
    else {
        cout << "result is false" << endl;
    }
    cout << "matches are: " << endl;
    for (int i = 0; i != matches3.size(); i++) {
        cout << "genome: " << matches3[i].genomeName << " length: " << matches3[i].length << " position: " << matches3[i].position << endl;
    }
    i++;
    delete test3;
    
    cout << "****TEST " << i << "*****" << endl;
    GenomeMatcher* test4 = new GenomeMatcher(4);
    test4->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    test4->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    test4->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    vector<DNAMatch> matches4;
    bool result4;
    result4 = test4->findGenomesWithThisDNA("GAATAC", 6, false, matches4);
    
    if (result4) {
        cout << "result is true" << endl;
    }
    else {
        cout << "result is false" << endl;
    }
    cout << "matches are: " << endl;
    for (int i = 0; i != matches4.size(); i++) {
        cout << "genome: " << matches4[i].genomeName << " length: " << matches4[i].length << " position: " << matches4[i].position << endl;
    }
    i++;
    delete test4;
    
    cout << "****TEST " << i << "*****" << endl;
    GenomeMatcher* test5 = new GenomeMatcher(4);
    test5->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    test5->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    test5->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    vector<DNAMatch> matches5;
    bool result5;
    result5 = test5->findGenomesWithThisDNA("GTATAT", 6, false, matches5);
    
    if (result5) {
        cout << "result is true" << endl;
    }
    else {
        cout << "result is false" << endl;
    }
    cout << "matches are: " << endl;
    for (int i = 0; i != matches5.size(); i++) {
        cout << "genome: " << matches5[i].genomeName << " length: " << matches5[i].length << " position: " << matches5[i].position << endl;
    }
    i++;
    delete test5;
    
    cout << "****TEST " << i << "*****" << endl;
    GenomeMatcher* test6 = new GenomeMatcher(4);
    test6->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    test6->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    test6->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    vector<DNAMatch> matches6;
    bool result6;
    result6 = test6->findGenomesWithThisDNA("GAATACG", 6, false, matches6);
    
    if (result6) {
        cout << "result is true" << endl;
    }
    else {
        cout << "result is false" << endl;
    }
    cout << "matches are: " << endl;
    for (int i = 0; i != matches6.size(); i++) {
        cout << "genome: " << matches6[i].genomeName << " length: " << matches6[i].length << " position: " << matches6[i].position << endl;
    }
    i++;
    delete test6;
    
    cout << "****TEST " << i << "*****" << endl;
    GenomeMatcher* test7 = new GenomeMatcher(4);
    test7->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    test7->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    test7->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    vector<DNAMatch> matches7;
    bool result7;
    result7 = test7->findGenomesWithThisDNA("GAAGGGTT",5, false, matches7);
    
    if (result7) {
        cout << "result is true" << endl;
    }
    else {
        cout << "result is false" << endl;
    }
    cout << "matches are: " << endl;
    for (int i = 0; i != matches7.size(); i++) {
        cout << "genome: " << matches7[i].genomeName << " length: " << matches7[i].length << " position: " << matches7[i].position << endl;
    }
    i++;
    delete test7;
    
    cout << "****TEST " << i << "*****" << endl;
    GenomeMatcher* test8 = new GenomeMatcher(4);
    test8->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    test8->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    test8->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    vector<DNAMatch> matches8;
    bool result8;
    result8 = test8->findGenomesWithThisDNA("GAAGGGTT", 6, false, matches8);
    
    if (result8) {
        cout << "result is true" << endl;
    }
    else {
        cout << "result is false" << endl;
    }
    cout << "matches are: " << endl;
    for (int i = 0; i != matches8.size(); i++) {
        cout << "genome: " << matches8[i].genomeName << " length: " << matches8[i].length << " position: " << matches8[i].position << endl;
    }
    i++;
    delete test8;
    
    cout << "****TEST " << i << "*****" << endl;
    GenomeMatcher* test9 = new GenomeMatcher(4);
    test9->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    test9->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    test9->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    vector<DNAMatch> matches9;
    bool result9;
    result9 = test9->findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCC", 12, false, matches9);
    
    if (result9) {
        cout << "result is true" << endl;
    }
    else {
        cout << "result is false" << endl;
    }
    cout << "matches are: " << endl;
    for (int i = 0; i != matches9.size(); i++) {
        cout << "genome: " << matches9[i].genomeName << " length: " << matches9[i].length << " position: " << matches9[i].position << endl;
    }
    i++;
    delete test9;
    
    cout << "****TEST " << i << "*****" << endl;
    GenomeMatcher* test10 = new GenomeMatcher(4);
    test10->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    test10->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    test10->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    vector<DNAMatch> matches10;
    bool result10;
    result10 = test10->findGenomesWithThisDNA("ACGTGCGAGACTTAGAGCC", 12, false, matches10);
    
    if (result10) {
        cout << "result is true" << endl;
    }
    else {
        cout << "result is false" << endl;
    }
    cout << "matches are: " << endl;
    for (int i = 0; i != matches10.size(); i++) {
        cout << "genome: " << matches10[i].genomeName << " length: " << matches10[i].length << " position: " << matches10[i].position << endl;
    }
    i++;
    delete test10;
    
    cout << "****TEST " << i << "*****" << endl;
    GenomeMatcher* test11 = new GenomeMatcher(4);
    test11->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    test11->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    test11->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    vector<DNAMatch> matches11;
    bool result11;
    result11 = test11->findGenomesWithThisDNA("GAAG", 3, false, matches11);
    
    if (result11) {
        cout << "result is true" << endl;
    }
    else {
        cout << "result is false" << endl;
    }
    cout << "matches are: " << endl;
    for (int i = 0; i != matches11.size(); i++) {
        cout << "genome: " << matches11[i].genomeName << " length: " << matches11[i].length << " position: " << matches11[i].position << endl;
    }
    i++;
    delete test11;
    
    cout << "****TEST " << i << "*****" << endl;
    GenomeMatcher* test12 = new GenomeMatcher(4);
    test12->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
    test12->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
    test12->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
    vector<DNAMatch> matches12;
    bool result12;
    result12 = test12->findGenomesWithThisDNA("GAAG", 5, false, matches12);
    
    if (result12) {
        cout << "result is true" << endl;
    }
    else {
        cout << "result is false" << endl;
    }
    cout << "matches are: " << endl;
    for (int i = 0; i != matches12.size(); i++) {
        cout << "genome: " << matches12[i].genomeName << " length: " << matches12[i].length << " position: " << matches12[i].position << endl;
    }
    i++;
    delete test12;
}

//int main() {
//
//     cout << "--- testing Trie.h ----" << endl;
//
//     Trie<int>* t = new Trie<int>();
//
//     t->insert("GATTACA", 42); // GATTACA -> {42}
//     t->insert("GATTACA", 17); // GATTACA -> {42, 17}
//     t->insert("GATTACA", 42); // GATTACA -> {42, 17, 42}
//     t->insert("GCTTACA", 12); // GCTTACA -> {12}
//
//     t->insert("GAT", 42);
//     t->insert("GAC", 55);
//     t->insert("GACT", 62);
//     t->insert("GTT", 48);
//     t->insert("GTTT", 15);
//     t->insert("ATTT", 12);
//     t->insert("ATTT", 16);
//     t->insert("ATCT", 14);
//     t->insert("TTTT", 42);
//
//     cout << "Searching for ATTT gives ";
//     vector<int> v = t->find("ATTT", false);
//     for (int i = 0; i != v.size(); i++) {
//     cout << v[i] << " ";
//     }
//     cout <<endl;
//
//
//     cout << "--- testing Genome.cpp ----" << endl;
//     string filename = "/Users/harshchobisa/Desktop/Gee-nomics/data/Halobacterium_jilantaiense.txt";
//     // Open the data file and get a ifstream object that can be used to read its
//     // contents.
//     ifstream strm(filename);
//     if (!strm)
//     {
//     cout << "Cannot open " << filename << endl;
//     return 0;
//     }
//     vector<Genome> vg;
//     bool success = Genome::load(strm, vg); // Load the data via the stream.
//     if (success)
//     {
//     cout << "Loaded " << vg.size() << " genomes successfully:" << endl;
//     for (int k = 0; k != vg.size(); k++) {
//     cout << vg[k].name() << endl;
//     cout << vg[k].length() << endl;
//     }
//
//     }
//     else
//     cout << "Error loading genome data" << endl;
//
//
//     cout << "--- testing GenomeMatcher.cpp ----" << endl;
//
//     GenomeMatcher* g = new GenomeMatcher(4);
//     cout << "min search length: " << g->minimumSearchLength() << endl;
//     g->addGenome(Genome("abc", "AGTN"));
//     g->addGenome(vg[0]);
//     cout << "successfully added genomes" << endl;
//
//
//    cout << "--- testing GenomeMatcher.cpp with spec tests----" << endl;
//
//     GenomeMatcher* test = new GenomeMatcher(2);
//
//
//
//
//    //test->findRelatedGenomes(toTest, test->minimumSearchLength() * 2, false, 10, res);
//    test->addGenome(Genome("nevada", "GGGGTTTTAAAACCCCACGTACGTACGTNANANANA"));
//    test->addGenome(Genome("new mexico", "GGGGTTTTAAAACCCCACGTACGTACGTNANANANA"));
//    test->addGenome(Genome("kansas", "GGGGTTTTAAAACCCCACGTACGTACGTNANANANA"));
//    test->addGenome(Genome("california", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
//    test->addGenome(Genome("utah", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
//
//    Genome toTest = Genome("TESTING", "AAATCCCTGGGGTTTTNANA");
//    vector<GenomeMatch> res;
//    test->findRelatedGenomes(toTest, 3, false, 10, res);
//
//    if (res.size() == 0)
//        cout << "EMPTY" << endl;
//    else
//    {
//        for (int x = 0; x < res.size(); x++)
//        {
//            cout << res[x].genomeName << " : " << res[x].percentMatch << endl;
//        }
//    }
//
//    delete test;
//
//    GenomeMatcher* temp = new GenomeMatcher(4);
//    temp->addGenome(Genome("1", "CGGTGTACNACGACTGGGGATAGAATATCTTGACGTCGTACCGGTTGTAGTCGTTCGACCGAAGGGTTCCGCGCCAGTAC"));
//    temp->addGenome(Genome("2", "TAACAGAGCGGTNATATTGTTACGAATCACGTGCGAGACTTAGAGCCAGAATATGAAGTAGTGATTCAGCAACCAAGCGG"));
//    temp->addGenome(Genome("3", "TTTTGAGCCAGCGACGCGGCTTGCTTAACGAAGCGGAAGAGTAGGTTGGACACATTNGGCGGCACAGCGCTTTTGAGCCA"));
//    vector<DNAMatch> matches;
//    bool result;
//    result = temp->
//    findGenomesWithThisDNA("GAAGGGTT", 5, false, matches);
//
//    if (result) {
//        cout << "result is true" << endl;
//    }
//    else {
//        cout << "result is false" << endl;
//    }
//    cout << "matches are: " << endl;
//    for (int i = 0; i != matches.size(); i++) {
//        cout << "genome: " << matches[i].genomeName << " length: " << matches[i].length << " position: " << matches[i].position << endl;
//    }
//
//    delete temp;
//}

////
////  main.cpp
////  Project4
////
////  Created by Harsh Chobisa on 3/7/19.
////  Copyright © 2019 Harsh Chobisa. All rights reserved.
////
//
//#include <iostream>
//#include "Trie.h"
//#include "provided.h"
//#include <istream>
//#include <fstream>
//#include <string>
//
//using namespace std;
//
//int main() {
////    Trie<int> t;
////    t.insert("GAT", 1);
////
////    t.insert("GAC", 2);
////    t.insert("GTT", 3);
////    t.insert("GTT", 4);
////    t.insert("GT", 5);
////    t.find("GAT", false);
////    t.find("GA", true);
////    t.display();
//
//    // Specify the full path and name of the gene data file on your hard drive.
//    string filename = "/Users/harshchobisa/Desktop/Gee-nomics/data/Halobacterium_jilantaiense.txt";
//    // Open the data file and get a ifstream object that can be used to read its
//    // contents.
//    ifstream strm(filename);
//    if (!strm)
//    {
//
//        cout << "Cannot open " << filename << endl;
//
//    }
//    vector<Genome> vg;
//    bool success = Genome::load(strm, vg); // Load the data via the stream. if (success)
//    if (success)
//    {
//        cout << "Loaded " << vg.size() << " genomes successfully:" << endl;
//        for (int k = 0; k==1; k++) {
//            cout << vg[k].name() << endl;
//            cout << vg[k].length();
////            for (int x = 0; x < vg[k].length(); x++)
////            {
////                cout << vg[k].
////            }
//            string s;
//
//        }
//    }
//    else
//        cout << "Error loading genome data" << endl;
//    GenomeMatcher * gm = new GenomeMatcher(200);
//    //Genome g = Genome("First Genome", vg[0].);
//    gm->addGenome(vg[0]);
//    //gm->addGenome(vg[1]);
//    cout << endl;
//}
//
//
//


//#include "provided.h"
//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <cctype>
//#include <cstdlib>
//using namespace std;
//
//// Change the string literal in this declaration to be the path to the
//// directory that contains the genome data files we provide, e.g.,
//// "Z:Desktop/archive/Geenomics/data" or "/Users/fred/cs32/Geenomics/data"
//
//const string PROVIDED_DIR = "/Users/harshchobisa/Desktop/Gee-nomics/data";
////const string PROVIDED_DIR = "Z:/Desktop/archive/Geenomics/data";
////const string PROVIDED_DIR = "/u/cs/ugrad/harsh/other";
//
//
//
//const string providedFiles[] = {
//    "Ferroplasma_acidarmanus.txt",
//    "Halobacterium_jilantaiense.txt",
//    "Halorubrum_chaoviator.txt",
//    "Halorubrum_californiense.txt",
//    "Halorientalis_regularis.txt",
//    "Halorientalis_persicus.txt",
//    "Ferroglobus_placidus.txt",
//    "Desulfurococcus_mucosus.txt"
//};
//
//void createNewLibrary(GenomeMatcher*& library)
//{
//    cout << "Enter minimum search length (3-100): ";
//    string line;
//    getline(cin, line);
//    int len = atoi(line.c_str());
//    if (len < 3 || len > 100)
//    {
//        cout << "Invalid prefix size." << endl;
//        return;
//    }
//    delete library;
//    library = new GenomeMatcher(len);
//}
//
//void addOneGenomeManually(GenomeMatcher* library)
//{
//    cout << "Enter name: ";
//    string name;
//    getline(cin, name);
//    if (name.empty())
//    {
//        cout << "Name must not be empty." << endl;
//        return;
//    }
//    cout << "Enter DNA sequence: ";
//    string sequence;
//    getline(cin, sequence);
//    if (sequence.empty())
//    {
//        cout << "Sequence must not be empty." << endl;
//        return;
//    }
//    if (sequence.find_first_not_of("ACGTNacgtn") != string::npos)
//    {
//        cout << "Invalid character in DNA sequence." << endl;
//        return;
//    }
//    for (char ch : sequence)
//        ch = toupper(ch);
//    library->addGenome(Genome(name, sequence));
//}
//
//bool loadFile(string filename, vector<Genome>& genomes)
//{
//    ifstream inputf(filename);
//    if (!inputf)
//    {
//        cout << "Cannot open file: " << filename << endl;
//        return false;
//    }
//    if (!Genome::load(inputf, genomes))
//    {
//        cout << "Improperly formatted file: " << filename << endl;
//        return false;
//    }
//    return true;
//}
//
//void loadOneDataFile(GenomeMatcher* library)
//{
//    string filename;
//    cout << "Enter file name: ";
//    getline(cin, filename);
//    if (filename.empty())
//    {
//        cout << "No file name entered." << endl;
//        return;
//    }
//    vector<Genome> genomes;
//    if (!loadFile(filename, genomes))
//        return;
//    for (const auto& g : genomes)
//        library->addGenome(g);
//    cout << "Successfully loaded " << genomes.size() << " genomes." << endl;
//}
//
//void loadProvidedFiles(GenomeMatcher* library)
//{
//    for (const string& f : providedFiles)
//    {
//        vector<Genome> genomes;
//        if (loadFile(PROVIDED_DIR + "/" + f, genomes))
//        {
//            for (const auto& g : genomes)
//                library->addGenome(g);
//            cout << "Loaded " << genomes.size() << " genomes from " << f << endl;
//        }
//    }
//}
//
//void findGenome(GenomeMatcher* library, bool exactMatch)
//{
//    if (exactMatch)
//        cout << "Enter DNA sequence for which to find exact matches: ";
//    else
//        cout << "Enter DNA sequence for which to find exact matches and SNiPs: ";
//    string sequence;
//    getline(cin, sequence);
//    int minLength = library->minimumSearchLength();
//    if (sequence.size() < minLength)
//    {
//        cout << "DNA sequence length must be at least " << minLength << endl;
//        return;
//    }
//    cout << "Enter minimum sequence match length: ";
//    string line;
//    getline(cin, line);
//    int minMatchLength = atoi(line.c_str());
//    if (minMatchLength > sequence.size())
//    {
//        cout << "Minimum match length must be at least the sequence length." << endl;
//        return;
//    }
//    vector<DNAMatch> matches;
//    if (!library->findGenomesWithThisDNA(sequence, minMatchLength, exactMatch, matches))
//    {
//        cout << "No ";
//        if (exactMatch)
//            cout << " matches";
//        else
//            cout << " matches or SNiPs";
//        cout << " of " << sequence << " were found." << endl;
//        return;
//    }
//    cout << matches.size();
//    if (exactMatch)
//        cout << " matches";
//    else
//        cout << " matches and/or SNiPs";
//    cout << " of " << sequence << " found:" << endl;
//    for (const auto& m : matches)
//    {
//        cout << "  length " << m.length << " position " << m.position << " in " << m.genomeName << endl;
//    }
//
//}
//
//bool getFindRelatedParams(double& pct, bool& exactMatchOnly)
//{
//    cout << "Enter match percentage threshold (0-100): ";
//    string line;
//    getline(cin, line);
//    pct = atof(line.c_str());
//    if (pct < 0  ||  pct > 100)
//    {
//        cout << "Percentage must be in the range 0 to 100." << endl;
//        return false;
//    }
//    cout << "Require (e)xact match or allow (S)NiPs (e or s): ";
//    getline(cin, line);
//    if (line.empty() || (line[0] != 'e' && line[0] != 's'))
//    {
//        cout << "Response must be e or s." << endl;
//        return false;
//    }
//    exactMatchOnly = (line[0] == 'e');
//    return true;
//}
//
//void findRelatedGenomesManual(GenomeMatcher* library)
//{
//    cout << "Enter DNA sequence: ";
//    string sequence;
//    getline(cin, sequence);
//    int minLength = library->minimumSearchLength();
//    if (sequence.size() < minLength)
//    {
//        cout << "DNA sequence length must be at least " << minLength << endl;
//        return;
//    }
//    double pctThreshold;
//    bool exactMatchOnly;
//    if (!getFindRelatedParams(pctThreshold, exactMatchOnly))
//        return;
//
//    vector<GenomeMatch> matches;
//    library->findRelatedGenomes(Genome("x", sequence), 2 * minLength, exactMatchOnly, pctThreshold, matches);
//    if (matches.empty())
//    {
//        cout << "    No related genomes were found" << endl;
//        return;
//    }
//    cout << "    " << matches.size() << " related genomes were found:" << endl;
//    cout.setf(ios::fixed);
//    cout.precision(2);
//    for (const auto& m : matches)
//        cout << " " << setw(6) << m.percentMatch << "%  " << m.genomeName << endl;
//}
//
//void findRelatedGenomesFromFile(GenomeMatcher* library)
//{
//    string filename;
//    cout << "Enter name of file containing one or more genomes to find matches for: ";
//    getline(cin, filename);
//    if (filename.empty())
//    {
//        cout << "No file name entered." << endl;
//        return;
//    }
//    vector<Genome> genomes;
//    if (!loadFile(filename, genomes))
//        return;
//    double pctThreshold;
//    bool exactMatchOnly;
//    if (!getFindRelatedParams(pctThreshold, exactMatchOnly))
//        return;
//
//    int minLength = library->minimumSearchLength();
//    for (const auto& g : genomes)
//    {
//        vector<GenomeMatch> matches;
//        library->findRelatedGenomes(g, 2 * minLength, exactMatchOnly, pctThreshold, matches);
//        cout << "  For " << g.name() << endl;
//        if (matches.empty())
//        {
//            cout << "    No related genomes were found" << endl;
//            continue;
//        }
//        cout << "    " << matches.size() << " related genomes were found:" << endl;
//        cout.setf(ios::fixed);
//        cout.precision(2);
//        for (const auto& m : matches)
//            cout << "     " << setw(6) << m.percentMatch << "%  " << m.genomeName << endl;
//    }
//}
//
//void showMenu()
//{
//    cout << "        Commands:" << endl;
//    cout << "         c - create new genome library      s - find matching SNiPs" << endl;
//    cout << "         a - add one genome manually        r - find related genomes (manual)" << endl;
//    cout << "         l - load one data file             f - find related genomes (file)" << endl;
//    cout << "         d - load all provided data files   ? - show this menu" << endl;
//    cout << "         e - find matches exactly           q - quit" << endl;
//}
//
//int main()
//{
//    const int defaultMinSearchLength = 10; ////////FIX!!!!!
//
//    cout << "Welcome to the Gee-nomics test harness!" << endl;
//    cout << "The genome library is initially empty, with a default minSearchLength of " << defaultMinSearchLength << endl;
//    showMenu();
//
//    GenomeMatcher* library = new GenomeMatcher(defaultMinSearchLength);
//
//    for (;;)
//    {
//        cout << "Enter command: ";
//        string command;
//        if (!getline(cin, command))
//            break;
//        if (command.empty())
//            continue;
//        switch(tolower(command[0]))
//        {
//            default:
//                cout << "Invalid command " << command << endl;
//                break;
//            case 'q':
//                delete library;
//                return 0;
//            case '?':
//                showMenu();
//                break;
//            case 'c':
//                createNewLibrary(library);
//                break;
//            case 'a':
//                addOneGenomeManually(library);
//                break;
//            case 'l':
//                loadOneDataFile(library);
//                break;
//            case 'd':
//                loadProvidedFiles(library);
//                break;
//            case 'e':
//                findGenome(library, true);
//                break;
//            case 's':
//                findGenome(library, false);
//                break;
//            case 'r':
//                findRelatedGenomesManual(library);
//                break;
//            case 'f':
//                findRelatedGenomesFromFile(library);
//                break;
//        }
//    }
//}



