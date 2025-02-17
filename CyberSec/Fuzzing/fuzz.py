from boofuzz import *

# Configuration du fuzzing
def fuzz():
    session = Session(
        target=Target(connection=SocketConnection("127.0.0.1", 5000, proto="tcp"))
    )


    # Fuzzing pour l'endpoint sécurisé
    s_initialize("Fuzzing Secure POST")
    with s_block("Request"):
        s_string('POST /secure HTTP/1.1\r\n', fuzzable=False)
        s_string('Host: 127.0.0.1\r\n', fuzzable=False)
        s_string('Content-Type: application/json\r\n', fuzzable=False)
        s_string('Content-Length: ', fuzzable=False)
        s_size("body", output_format="ascii")
        s_string("\r\n\r\n", fuzzable=False)
        with s_block("body"):
            s_string('{ "number": ', fuzzable=False)
            s_int(-100,-5)  # On fuzz ici avec des valeurs négatives et positives
            s_string(" }", fuzzable=False)

    session.connect(s_get("Fuzzing Secure POST"))

    session.fuzz()

if __name__ == "__main__":
    fuzz()