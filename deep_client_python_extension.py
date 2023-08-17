from deep_client_interface import DeepClient

def make_deep_client(token, url):
    if not token:
        raise ValueError("No token provided")
    if not url:
        raise ValueError("No url provided")
    return DeepClient()