# AVA API


# Choix des technologies:


# Serialisaton:

- Google Protocol Buffer:

Language de serialisation neutre, indépendant de la plateforme et conçu pour sérialiser des données structurées.
Semblable au XML mais plus rapide plus léger plus performant.
De plus il permet de choisir nous mêmes comment structurer les données.


# Communication:

- gRPC:

Framework RPC open-source. Il permet de définir ses propres services grâce au protocole buffers.
Fonctionne avec tous les languages et les plateformes.
Offre de nombreux avantages:

* Bi-directionnal streaming

* systemes d'authentification intégrés:
  Credentials channels & calls
  Google token-based authentication


* Error handling & debugging
