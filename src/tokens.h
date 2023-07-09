enum TOKENS {
        /// https://en.wikipedia.org/wiki/666_(number)
        EoF = 666,

        ADD,
        SUB,
        MUL,
        DIV,

        RET,

        DIGIT,
        IDENT,

        KEYWORD,
        WHILE,
        SETQ,
        DEFUN,
        PRINT,

        GREATER,
        LESSER,

        S_L_PAREN,
        S_R_PAREN,
        ERROR,

} typedef TOKENS;

extern TOKENS tokens;
