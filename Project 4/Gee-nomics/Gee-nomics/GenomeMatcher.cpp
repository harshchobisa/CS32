#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "Trie.h"
using namespace std;

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int m_minSearchLength;
    Trie<DNAMatch> t;
    int m_numGenomes;
    vector<Genome> g;
    unordered_map<string, int> nameToPosition;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSearchLength = minSearchLength;
    m_numGenomes = 0;
}

//adds a genome to the trie. Does this by taking fragments of the genome sequence and inserting into the trie
void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    g.push_back(genome);
    int limit = genome.length();
    for (int x = 0; x + m_minSearchLength <= limit; x++)
    {
        string s;
        if(genome.extract(x, minimumSearchLength(), s)) //extract fragments
        {
            //string label = "Genome " + to_string(m_numGenomes) + ", position " + to_string(x);
            DNAMatch dna = DNAMatch();
            dna.genomeName = genome.name();
            dna.length = m_minSearchLength;//genome.length();
            dna.position = x;
            t.insert(s, dna);
            nameToPosition.insert(pair<string, int>(genome.name(), m_numGenomes));
        }
    }
    m_numGenomes++;
}

//getters for m_minSearchLength
int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;
}

//matches found in trie to look through a map of Genomes to see if there are matches. Then,
//loop through the the hits and compare characters one by one, and if we find the longest run,
//add to a map. Loop through final map and add to vector.
bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    if (minimumLength < minimumSearchLength())
        return false;
    
    
    //maps that are used to improve run time
    unordered_map<string, int> longestLength;
    unordered_map<string, int> longestPos;
    
    vector<DNAMatch> found = t.find(fragment.substr(0, minimumSearchLength()), exactMatchOnly);
    
    for (int currentHit = 0; currentHit < found.size(); currentHit++)
    {
        unordered_map<string, int>::const_iterator iter = nameToPosition.find(found[currentHit].genomeName);
        if (iter == nameToPosition.end())
            continue;
        int genomeNum = iter->second;
        bool updated = false;
        if (found[currentHit].genomeName == g[genomeNum].name()) //if we find a match
        {
            string genomeFragment;
            int gFragLength = fragment.length();
            bool madeMistake = exactMatchOnly;
            int adjust = 0;
            int animani = found[currentHit].position;
            while (g[genomeNum].extract(animani, fragment.length() - adjust, genomeFragment) == false)
            {
                adjust++; //adjustment in case we are at the end of the string. don't want to throw away ending bits
            }
            
            if (fragment.substr(0, minimumSearchLength()) != genomeFragment.substr(0, minimumSearchLength()))
                madeMistake = true;
            
            gFragLength = genomeFragment.length();
            for (int x = minimumSearchLength(); x < genomeFragment.length(); x++)
            {
                //g[genomeNum].extract(found[currentHit].position + x, 1, fragToCheck);
                if (genomeFragment[x] != fragment[x]) //if we have not made a mistake yet, update that we have. else try to insert into vector
                {
                    if (madeMistake == false)
                        madeMistake = true;
                    else
                    {
                        updated = true;
                        
                        unordered_map<string, int>::iterator curLength = longestLength.find(found[currentHit].genomeName);
                        unordered_map<string, int>::iterator curPos = longestPos.find(found[currentHit].genomeName);
                        if (curLength == longestLength.end())
                        {
                            longestLength.insert(make_pair(found[currentHit].genomeName, x));
                            longestPos.insert(make_pair(found[currentHit].genomeName, found[currentHit].position));
                        }
                        else if (x > curLength->second)
                        {
                            curLength->second = x;
                            curPos->second = found[currentHit].position;
                        }
                        break;
                    }
                }
            }
            if (!updated) //if we have gone through the loop and reached the end of the fragment with at most one mistake, add to vector
            {
                unordered_map<string, int>::iterator curLength = longestLength.find(found[currentHit].genomeName);
                unordered_map<string, int>::iterator curPos = longestPos.find(found[currentHit].genomeName);
                if (curLength == longestLength.end())
                {
                    longestLength.insert(make_pair(found[currentHit].genomeName, gFragLength));
                    longestPos.insert(make_pair(found[currentHit].genomeName, found[currentHit].position));
                }
                else if (gFragLength > curLength->second)
                {
                    curLength->second = gFragLength;
                    curPos->second = found[currentHit].position;
                }
            }
        }
    }
    //now loop through map and add to the vector
    for (int mapInd = 0; mapInd < g.size(); mapInd++)
    {
        unordered_map<string, int>::iterator itLength = longestLength.find(g[mapInd].name());
        unordered_map<string, int>::iterator itPos = longestPos.find(g[mapInd].name());
        if (itLength != longestLength.end() || itPos != longestPos.end())
        {
            DNAMatch toInsert;
            toInsert.genomeName = g[mapInd].name();
            toInsert.position = itPos->second;
            toInsert.length = itLength->second;
            if (itLength->second >= minimumLength)
            {
                matches.push_back(toInsert);
            }
        }
    }
    
    return (matches.size() != 0);
}

//uses a map to map DNA names to count of how many hits there are. using this count, calculate the percentage match
bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    unordered_map<string, int > map;
    unordered_map<std::string,int>::iterator element;
    
    //this loop creates the map
    for (int pos = 0; pos < query.length(); pos += fragmentMatchLength) //increase by fragmentMatchLength to correctly create segments to evaluate
    {
        vector<DNAMatch> matches;
        string frag;
        query.extract(pos, fragmentMatchLength, frag);
        findGenomesWithThisDNA(frag, fragmentMatchLength, exactMatchOnly, matches);

        for (int match = 0; match < matches.size(); match++)
        {
            //cout << matches[match].genomeName << ": length : " << matches[match].length << " position : " << matches[match].position << endl;
            element = map.find(matches[match].genomeName);
            if (element == map.end()) //if we have not added the element to the map yet, insert it, else increase its count
            {
                map.emplace(matches[match].genomeName, 1);
            }
            else
            {
                element->second++;
            }
        }
    }
        
    element = map.begin();
    while (element != map.end()) //iterate through the map and calculate the percentages for each genome
    {
        int numTotalSequences = (query.length()/fragmentMatchLength);
        double percentage = (1.0*element->second) / numTotalSequences;
        percentage = percentage * 100;
//        cout<< percentage << endl;
//        cout << element -> first;
        if (percentage >= matchPercentThreshold)
        {
            GenomeMatch toAdd;
            toAdd.genomeName = element->first;
            toAdd.percentMatch = percentage;
            results.push_back(toAdd);
        }
        element++;
    }
    
    sort(results.begin(), results.end(), greater<GenomeMatch>()); //sort in ascending order

    
    return (results.size() != 0);
}

//comparison operator for GenomeMatch, needed for the sort function
bool operator>(const GenomeMatch &a, const GenomeMatch &b)
{
    if (a.percentMatch == b.percentMatch)
    {
        return (a.genomeName < b.genomeName);
    }
    return (a.percentMatch > b.percentMatch);
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
