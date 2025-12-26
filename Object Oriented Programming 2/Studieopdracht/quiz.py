#!/usr/bin/env python3
"""
Simple C++ syntax quiz for the terminal (Dutch).
Run: `python quiz.py` for interactive mode.
Run: `python quiz.py --auto` to run a self-test (no interaction).

The quiz expects short snippets or tokens as answers. Matching is whitespace-insensitive.
"""
import sys
import re

questions = [
    {
        "prompt": "1) Declare a pointer to int named p (include semicolon),\n   bijv. 'int* p;'",
        "checks": [lambda s: re.sub(r"\s+", "", s) == "int*p;"],
        "hint": "Gebruik '*' om een pointer te declareren, bv. int* p;",
        "explanation": "Pointer declaratie: 'int* p;' betekent dat p een adres naar een int opslaat."
    },
    {
        "prompt": "2) Declare a reference to int named r (include semicolon),\n   bijv. 'int& r;'",
        "checks": [lambda s: re.sub(r"\s+", "", s) == "int&r;"],
        "hint": "Gebruik '&' voor een reference, bv. int& r;",
        "explanation": "Reference (alias): 'int& r;' bindt r direct aan een bestaande int."
    },
    {
        "prompt": "3) Write a const reference parameter for std::string named s (no semicolon required),\n   bijv. 'const std::string& s'",
        "checks": [lambda s: "conststd::string&s" in re.sub(r"\s+", "", s)],
        "hint": "Gebruik 'const' en '&' samen: const std::string& s",
        "explanation": "Const reference voorkomt kopiëren en beschermt tegen wijziging in de functie."
    },
    {
        "prompt": "4) How do you declare a pure virtual method f that returns void?\n   (include ';')",
        "checks": [lambda s: re.sub(r"\s+", "", s).startswith("virtualvoidf()=0;")],
        "hint": "Gebruik 'virtual', methode naam en '= 0' om pure virtual te maken.",
        "explanation": "Pure virtual methode: 'virtual void f() = 0;' maakt de klasse abstract."
    },
    {
        "prompt": "5) After using operator>> you want to ignore the rest of the line. Give one correct statement you could use (short form ok).",
        "checks": [
            # check for ignore + numeric_limits pattern
            lambda s: ("ignore(" in s.replace(" ", "") and "numeric_limits" in s),
            # or getline with ws
            lambda s: "getline(" in s and "std::ws" in s
        ],
        "hint": "Gebruik std::cin.ignore(...) of std::getline(std::cin >> std::ws, s)",
        "explanation": "Na >> blijft vaak een newline in buffer; std::cin.ignore(...) of std::ws voor getline helpt."
    },
    {
        "prompt": "6) Create a unique_ptr to a Weapon named w (short form, show make_unique usage),\n   e.g. 'auto w = std::make_unique<Weapon>(\'Ex\',10);'",
        "checks": [lambda s: "make_unique" in s.replace(" ", "")],
        "hint": "Gebruik std::make_unique<T>(...) om een std::unique_ptr aan te maken.",
        "explanation": "std::make_unique<Weapon>(...) maakt en geeft een unique_ptr terug (aanbevolen boven raw new)."
    }
]


def normalize_answer(ans: str) -> str:
    # strip leading/trailing and collapse internal whitespace
    return ans.strip()


def ask_interactive():
    print("C++ Syntax Quiz - typ de juiste syntax en druk Enter. (Typ 'hint' voor hint.)\n")
    score = 0
    for q in questions:
        print(q["prompt"])
        while True:
            try:
                ans = input("> ")
            except EOFError:
                print("\nEinde van invoer.")
                return
            if ans.lower() == "hint":
                print("Hint:", q["hint"]) 
                continue
            ans_norm = normalize_answer(ans)
            ok = False
            for check in q["checks"]:
                try:
                    if check(ans_norm):
                        ok = True
                        break
                except Exception:
                    continue
            if ok:
                print("Correct! ")
                score += 1
            else:
                print("Fout. Antwoord voorbeeld:", q["explanation"]) 
            print()
            break
    print(f"Einde quiz. Score: {score}/{len(questions)}")


def run_auto_test():
    # automatic answers for quick verification
    auto_answers = [
        "int* p;",
        "int& r;",
        "const std::string& s",
        "virtual void f() = 0;",
        "std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\\n');",
        "auto w = std::make_unique<Weapon>(\"Ex\", 10);"
    ]
    print("Running auto test...\n")
    score = 0
    for q, a in zip(questions, auto_answers):
        print(q["prompt"]) 
        print(">", a)
        ans_norm = normalize_answer(a)
        ok = False
        for check in q["checks"]:
            try:
                if check(ans_norm):
                    ok = True
                    break
            except Exception:
                continue
        if ok:
            print("Correct (auto)")
            score += 1
        else:
            print("Auto test failed for question:", q["prompt"]) 
        print()
    print(f"Auto test score: {score}/{len(questions)}")


if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] in ('--auto', 'auto'):
        run_auto_test()
    else:
        ask_interactive()
