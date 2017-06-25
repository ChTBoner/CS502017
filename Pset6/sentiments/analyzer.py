import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer. Load positive and negative words"""

        # open and parse positive words
        pos_words_file = open(positives)
        self.pos_words = set()
        for line in pos_words_file:
            if not line.startswith(';'):
                self.pos_words.add(line.rstrip())
        pos_words_file.close()

        neg_words_file = open(negatives)
        self.neg_words = set()
        for line in neg_words_file:
            if not line.startswith(';'):
                self.neg_words.add(line.rstrip())
        neg_words_file.close()


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        self.tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = self.tokenizer.tokenize(text)

        score = 0
        for token in tokens:
            if token.lower() in self.pos_words:
                score += 1
            elif token.lower() in self.neg_words:
                score -= 1

        return score
