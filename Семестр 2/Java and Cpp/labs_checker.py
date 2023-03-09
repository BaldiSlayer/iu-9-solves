import requests, time

USER = {
    'email': 'Jedi.Aleksey@yandex.ru',
    'password': 'saklfasdlfdsal;jk'
}

s = requests.session()
r = s.post('https://iu9.yss.su/auth/login', data=USER)

for i in range(10, 98):
    url = f'https://iu9.yss.su/main/lab_id{i}/download'
    r0 = s.get(url)
    if r0.status_code < 300:
        with open(f'{i}.pdf', 'wb') as f:
            f.write(r0.content)
    print(i)
    time.sleep(1)
