---
name: projects
layout: default
menus:
  - title: Projets étudiants
    href: projects.html
    icon: files-o
title: Sujets de projet proposés
---

# Sujets de projets proposés

{% for p in site.projects %}
- [{{ p.title }}]({{ site.baseurl }}{{ p.url }}) <small>({{ p.keywords | join: ', ' }}.)</small>
{% endfor %}
