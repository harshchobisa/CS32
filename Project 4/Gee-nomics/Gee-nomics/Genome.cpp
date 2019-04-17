#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
using namespace std;

class Genome;
class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_sequence;
    int m_size;
};


GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_sequence = sequence;
    m_size = sequence.size();
}

//load function that loads an external data file
bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    if (!genomeSource)
        return false;
    
    std::string s;
    string name;
    string sequence;
    getline(genomeSource, s);
    
    name = s.substr(1);
    if (name == "") return false;
    // getline returns infile; the while tests its success/failure state
    while (getline(genomeSource, s))
    {
        if (s == "")
        {
            return false;
        }
        if (s[0] == '>') //we know we have reached a name, and the end of the last sequence
        {
            int limit = sequence.size();
            if (sequence == "")
                return false;
            for (int x = 0; x < limit; x++)
            {
                if (sequence[x] != 'A' && sequence[x] != 'C' && sequence[x] != 'G' && sequence[x] != 'N' && sequence[x] != 'T') //check for validity of string
                    return false;
                toupper(sequence[x]);
            }
            genomes.push_back(Genome(name, sequence));
            name = s.substr(1);
            sequence = "";
            if (name == "") return false; //check validity of string
        }
        else
            sequence = sequence + s;

    }
    genomes.push_back(Genome(name, sequence));

    return true;
}

int GenomeImpl::length() const
{
    return m_size;
}

string GenomeImpl::name() const
{
    return m_name;
}

//as long as we are not told to extract a string that is too large, extract
bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (position + length > m_size)
        return false;
    fragment = m_sequence.substr(position, length);
    return true;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
