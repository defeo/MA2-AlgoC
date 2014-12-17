---
layout: index
title: Sujets de projet proposés
---

# Sujets de projets proposés

{% for p in site.projects %}
- [{{ p.title }}]({{ site.baseurl }}{{ p.url }}) <small>({{ p.keywords | join: ', ' }}.)</small>
{% endfor %}
