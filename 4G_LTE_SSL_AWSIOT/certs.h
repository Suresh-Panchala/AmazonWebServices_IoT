const char cacert[] PROGMEM =
"-----BEGIN CERTIFICATE-----\n"
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n"
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n"
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n"
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n"
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n"
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n"
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n"
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n"
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n"
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n"
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n"
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n"
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n"
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n"
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n"
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n"
"rqXRfboQnoZsG4q5WTP468SQvvG5\n"
"-----END CERTIFICATE-----\n";

const char clientcert[] PROGMEM = 
"-----BEGIN CERTIFICATE-----\n"
"MIIDWjCCAkKgAwIBAgIVAPHEWOXKZZ0B5CVWXl3OyIKKnvyPMA0GCSqGSIb3DQEB\n"
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDA3MTMwNzMx\n"
"MjJaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCk9KkIluomai92+PxL\n"
"dzEK75zIhPYdbfdRc+g1WA2d204t1Sijn4nFTt8MGVz0A2cXJ+AIey5tMjaETBn6\n"
"uL29VbCqRxeQ51LfdQJWNlul5okmJujMAHZKPBqqPZ5JfrAT9CBiiepEUQ9FVahl\n"
"71jiSu1CYRVJWe/r1/+RdjffVCnxCwim5XwWjRHenP0KZjJmW6P2uJPJxJyGJmdg\n"
"xp0rRIHdpNcSUDKyIKhRa9LKv5vva63m4tkJ9ZndeLGT6mmVyIJF6O/+2PgLCA3G\n"
"1fJb7RWSzDx7Y9kr0fJ9m9q2AFj8gfcS48rIa0Fwbmcme0MBJ5+v18dVSxkEEwQ0\n"
"wql9AgMBAAGjYDBeMB8GA1UdIwQYMBaAFFV6pHtR5atwf4clypJqTiTkveA/MB0G\n"
"A1UdDgQWBBQipWGOYk6NMGlgSWPGCw/uYrJvejAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEADks1Mcu9Bq8yc5Uef/E5JQXh\n"
"I7Hs8r+gSh29HGJzLkUxtBxCnSjWQ3PnHwCubjGaG0DB21fkzjqM9HFWss0P0Hst\n"
"JlWS3vKmnkTu9RlHYqyjbuPT1gn8VE2m1xglcp2tqrwgJerWy7XLUDUNYnlbQZw4\n"
"aKDhzoF3T+E27Si89/9WKQ0FAZJ+fXKG4O6P7vlIs46q0Jv0W9J18AxbTWQCgCXl\n"
"bVAjw6iPfT5VPDRz+bbaekB0rxYH/eHG9QDIlGXzn7Vv5badqKVSuN8HuYaQlLM9\n"
"2S2cMOEAOn1cSI2S96SdZXi2jbPfnYr4haUxZYiDImglZJTf62Gb45e6t1s9eg==\n"
"-----END CERTIFICATE-----\n";
const char clientkey[] PROGMEM = 
"-----BEGIN RSA PRIVATE KEY-----\n"
"MIIEowIBAAKCAQEApPSpCJbqJmovdvj8S3cxCu+cyIT2HW33UXPoNVgNndtOLdUo\n"
"o5+JxU7fDBlc9ANnFyfgCHsubTI2hEwZ+ri9vVWwqkcXkOdS33UCVjZbpeaJJibo\n"
"zAB2Sjwaqj2eSX6wE/QgYonqRFEPRVWoZe9Y4krtQmEVSVnv69f/kXY331Qp8QsI\n"
"puV8Fo0R3pz9CmYyZluj9riTycSchiZnYMadK0SB3aTXElAysiCoUWvSyr+b72ut\n"
"5uLZCfWZ3Xixk+pplciCRejv/tj4CwgNxtXyW+0Vksw8e2PZK9HyfZvatgBY/IH3\n"
"EuPKyGtBcG5nJntDASefr9fHVUsZBBMENMKpfQIDAQABAoIBAQCkQOMYJH4fpliB\n"
"FUjUNGlnRFVP7eXMRDWiq9GrXHSinT9pr/l5hGEBUZoUSCUg7Up36kLQ7ye5n+hd\n"
"MBImcFKu92alB4lVxqHk1HRxOEtmFPq4PMJOcJ9ZKCQ9JII7GKVoGQ0uUbouMLEO\n"
"D09RwVU2b/l0wYsasS2QIFLhm1/jRid2ZB7X+5fk5UtYbJhsfCHF5xA3FL1lwqtp\n"
"xufHvb0EmFvjGj5rNi4u8W/Io+87jhqlFIOm+Z3sZYyeDgTXmhGHv3ThY4eIsKkP\n"
"tol3n7ry/OpR8w10o7H1suHVgHuBa2aRHQWYCu2+k6q+gSQdOpkRH2DwyUDus/3p\n"
"MQz21V7BAoGBANiG1P9dzYOT5BBXzgTAW5ZLtbvdj7v+6LGkpwcFL05uh9Bbs9zC\n"
"aOC9IuOazhh2Kddid73QznqkDwnpj3HcQe9A73xB1KFOlB71V7rCdIYixYLJAYCO\n"
"U0PmOnv/JQIOh3TN5XSngZNyqvHx1RpGwjOx2T9t8ldo+1l1wHl+BF45AoGBAMMH\n"
"CsMOuibAYtkZL/zL2wYry7EDMglMHje0eislKK3XrpOyGyaWh2pqba2DWFUZKec3\n"
"aeNw263wQ1exNi5dMVPPMub9isxwm4V0f68EH/KMTgE218ixPHZSlrwrvrOtanCA\n"
"edIKyMrwiPwX29iE/9PdB9WXJdIe/dwEC2tSxWVlAoGAay2SkTUlXVP/N/e+iquM\n"
"qkCfnHZ3h18OX6BY7Sir2e7sWz6JMWUp9NSqSG+ARKt42pxrGRIaoqpCp21tC7cz\n"
"C/LgmGkdjxsORqS64D8Q3rSnf61viOrqXFnB6U7KStJWSoMAaVXg1dOUul4yVedg\n"
"iaYnGzaZFptoj0eyFnFCSEECgYBdgPnS7TOosqJxzdapEB/RhJvjIVITDRCLypas\n"
"KuOm/Xpwy3qi9Ja2GZK+FvP50Ne7SGEXL5vTeBcBazA76Ghm8zdHchXi0LZvtJwn\n"
"EAY1JrmbcWzhhsAjRpOIYjzLLoCSsbY2Uv9T9SDoJJQ96f4x2I4SBKaYaE1z9+h1\n"
"qziC1QKBgCBF9f8912+mLSd4F7RXyLnrvKVTAUvTKHqcMY0qh8BHt1I1RJ2ayOvO\n"
"miSLdNVEBPHxcQmCww+MIRVqheT4QV+L+JzFahuh9mrv1Avfwp4ue2mwbXF2/gsm\n"
"CMLiCweyRA267XKszg9iVSdg98iwSEtihPoNDMWpDdc2Trg4NjxS\n"
"-----END RSA PRIVATE KEY-----\n";
