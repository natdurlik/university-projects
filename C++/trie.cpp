struct TrieNode {
    bool end=false;
    unordered_map<char,unique_ptr<TrieNode>> children;
};

class Trie {
public:
    unique_ptr<TrieNode> root;
    Trie () {
        root=make_unique<TrieNode>();
    }
    void addWord(string word) {
        if(!word.empty()) {
            TrieNode*p=root.get();
            for(char c:word) {
                if(!p->children[c]) p->children[c]=make_unique<TrieNode>();
                p=p->children[c].get();
            }
            p->end=true;
        }
    }
    bool search(string word) {
        if(!word.empty()) {
            return search_aux(root.get(),word,0);
        }
        return false;
    }
    bool search_aux(TrieNode*p,string word,int i) {
        if(i>=word.size()) return p->end;
        if(word[i]!='.') {
            if(!p->children[word[i]]) return false;
            return search_aux(p->children[word[i]].get(),word,i+1);
        }
        for(auto& [c,node]:p->children) {
            if(node&&search_aux(node.get(),word,i+1)) return true;
        }
        return false;
    }
};