# 📄 Document Similarity Checker (C++)

A command-line based **document similarity and plagiarism detection** tool written in **C++**, which compares two text files using weighted **n-gram Jaccard similarity**.

---

## 🚀 Features

- Command-line interface (CLI) usage  
- Reads and processes text files safely  
- Normalizes text (case folding & punctuation handling)  
- Stop-word filtering
- Tokenizes content into words 
- Generic n-gram generation (unigram / bigram / trigram) 
- Uses **Jaccard Similarity** to compute document overlap  
- Weighted similarity scoring
- Avoids division-by-zero edge cases  
- Uses ordered STL containers and algorithms  

---

## 🧠 Algorithm Used

The similarity is computed using the **Jaccard Index**:

\[
J(A,B)= ∣A∩B∣/∣A∪B∣
\]

Where:

- **A** = set of unique words from file 1  
- **B** = set of unique words from file 2  

The result is reported as a **percentage similarity**.

---

## 🛠️ Implementation Details

### Core Pipeline

1. **Read file contents**
2. **Normalize text**
   - Convert to lowercase
   - Replace punctuation with spaces
3. **Tokenize text**
   - Split text into words using `stringstream`
4. **Convert tokens into ordered sets (`std::set`)**
5. **Compute intersection and union**
   - Using `std::set_intersection`
   - Using `std::set_union`
6. **Calculate similarity score of unigram bigram and trigram and find the final similarity score**

---

## 📦 Technologies & Libraries Used

- **C++ (STL)**
- `<fstream>` — file handling  
- `<set>` — ordered unique storage  
- `<algorithm>` — set operations  
- `<sstream>` — tokenization  
- `<iterator>` — inserter adapters  

---
## ✅ Strengths
- Clear separation of concerns
- (Reading, normalization, tokenization, comparison)

- Correct mathematical model (Jaccard Index)

- Robust edge-case handling (empty union)

- Effective use of STL algorithms

- Readable and maintainable code

- Counts common stop-words (the, is, and)

- Support n-grams (unigrams / bigrams / trigrams) for better plagiarism detection

## ⚠️ Current Limitations
- Uses std::set (tree-based, O(log n) set operations)

- No stemming or lemmatization

## 🔮 Future Improvements
- Planned enhancements to make this a 90+ quality project:

- **🔧 Performance & Memory:**
- Switch to std::unordered_set for faster lookups

- Manual intersection to avoid sorting overhead

- **🧠 Text Processing**
- Implement stemming (e.g., run vs running)

- **🧵 Modern C++**
- Use std::string_view (C++17+) to reduce string allocations

## ▶️ How to Compile and Run

### Compile
```bash
g++ main.cpp -o check
./check file1.txt file2.txt
```



