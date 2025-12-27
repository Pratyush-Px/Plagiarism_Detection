# 📄 Document Similarity Checker (C++)

A command-line based **document similarity checker** written in **C++**, which computes the similarity between two text files using the **Jaccard Index**.  
This project demonstrates clean program structure, correct use of STL algorithms, and foundational techniques used in plagiarism detection systems.

---

## 🚀 Features

- Command-line interface (CLI) usage  
- Reads and processes text files safely  
- Normalizes text (case folding & punctuation handling)  
- Tokenizes content into words  
- Uses **Jaccard Similarity** to compute document overlap  
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
6. **Calculate similarity score**

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

## ⚠️ Current Limitations
- Uses std::set (tree-based, O(log n) insertions)

- Counts common stop-words (the, is, and)

- No stemming or lemmatization

- Uses word-level comparison only (unigrams)

## 🔮 Future Improvements
- Planned enhancements to make this a 90+ quality project:

- **🔧 Performance & Memory:**
- Switch to std::unordered_set for faster lookups

- Manual intersection to avoid sorting overhead

- **🧠 Text Processing**
- Add stop-word filtering

- Implement stemming (e.g., run vs running)

- Support n-grams (bigrams / trigrams) for better plagiarism detection

- **🧵 Modern C++**
- Use std::string_view (C++17+) to reduce string allocations

## ▶️ How to Compile and Run

### Compile
```bash
g++ main.cpp -o check
./check file1.txt file2.txt
```



