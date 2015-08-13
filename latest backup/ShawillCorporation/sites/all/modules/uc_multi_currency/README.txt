Ubercart Multi-Currency
=======================

Written for Drupal 7, Ubercart 3.

Modifications to Ubercart core

This is the weakest part, I know. :-) Until the necessary changes are included in Ubercart (see the discussion at 
https://www.drupal.org/node/1097668), Ubercart has to be modified in simple ways but in many places. The module contains 
a diff file with all the required changes. This isn't a nice solution and certainly is only an intermediate one until 
these changes can be incorporated into the core. Decide for yourself if you're ready to use the module with these extra 
requirements for now.

Functioning of the module

Apart from the required core modifications mentioned above, the module is fully functional. Upon installation a new 
configuration item will appear in Store > Configuration. You can import your currency files there (the module only comes 
with a handful of those but if you look into them, the format is straightforward and it's very easy to add new currency 
files; contributions to this are very welcome).

On the second tab, you can also decide which selection plugins you want to enable to determine the actual currency used. 
You can let the user select it (a Choose currency block appears among your blocks that you can place anywhere), 
determine the currency based on the current language of the site, link currencies to user roles, product types, etc. The 
plugin architecture is rather simple, so new plugins can be added with relative ease.

Apart from these settings, the rest is already automatic. Wherever Drupal presents prices (product prices, attribute and 
options prices, etc) you will receive a replacement table instead of the original price specification fields that allows 
you to specify prices in all the currencies actually enabled and in use on your site.
