How to Compile: type "make"

How to Execute file: type "./P3 [filename]

File must include: 

Lexical Definitions
• Case sensitive
• Comments start with ! and end with !
  o Comments must be handled during preprocessing and should not be included in your FSA
• Alphabet:
  o All upper- and lower-case English letters, digits, plus the extra characters as shown below, plus
white space
  o No other characters are allowed and they must generate errors
• Each scanner error must display "SCANNER ERROR:" followed by input string and line number
• Token type t1
  o Begin with a single “ or a single #
  o followed by one or more digits (0-9)
     e.g. “0, #1000, “046 are all valid; while #, 3#, 10, ““1 are all invalid tokens
• Token type t2
  o Begin with one or more letters, (a-z, A-Z)
  o Followed by one or more digits (0-9)
     e.g. b0, ZaYbbb4, x99448, Y00 are all valid and zJm, b&3, 10kT, 94 are all invalid tokens
• Token type t3
  o $ % & ‘ ( ) * + , - . / // these characters correspond to ascii numbers 36 to 47

  BNF
(Ensure this uses only tokens detected in your P2, no exceptions.)
S is the starting nonterminal. Lowercase and punctuation marks are terminals, uppercase letters represent
nonterminals, and the pipe symbol ‘|’ separates the production rule options.
S -> A K '
A -> B | C | G H F J ' S
B -> $ t1 | * t1
C -> - t1 J
D -> E H D | ε
E -> ( | )
F -> , | . | +
G -> % | &
H -> t1 | t2
J -> ' H D
K -> S K | ε
