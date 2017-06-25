### Boktraskare
                                                  
A tree walking interpreter

#### Roadmap
##### Scanner

- [x] Finish outline for the scanner (mathematical expressions)
The outline of the scanner should demonstrate how to identify lexemes in the source.
For starters, simple mathematical expressions should be enough to move on to the parser. 
After having a functional scanner

- [ ] Define a grammar in [EBNF](https://www.wikiwand.com/en/Extended_Backus%E2%80%93Naur_form)
This is essentially constructing a language and a syntax, which we need to do before
knowing which tokens to actually produce. Probably easiest to begin with just math
expressions first (no identifiers, no variables, no strings, no statements) and
figure out how parsing and evaluating works before adding on the rest of it.

- [ ] Handle identifiers
Identifiers are user-defined words in the source code, like variable names. Anything
that's not a keyword (see below), begins with an alphabetic character followed by any 
number of alphanumeric characters is to be scanned as an identifier.

- [ ] Handle keywords
Keywords are things like "function", "for" and "while". These will probably not have
their own function in the scanner, instead, for each identifier we find, we will look
it up in a table of keywords, and if it exists we know it's a keyword and we'll return
a keyword token instead.

- [ ] Handle floating point numbers
With the "." inbetween. This is trivially in the scanner, however, the parser needs to
know that this is a floating point number. In our language we probably want to handle
everything as a float, so a 1 is actually a 1.0, for simplicity. Need to do more research
on how this will be implemented.

##### Parser
- [ ] Finish skeleton of the parser
- [ ] Implement every EBNF production as a function to produce a tree



##### Evaluation
- [ ] Do more research on how evaluation works
