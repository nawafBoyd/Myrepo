/**
 * @file
 * Utility functions to display settings summaries on vertical tabs.
 */

(function ($) {

Drupal.behaviors.ucProductFieldsetSummaries = {
  attach: function (context) {
    $('fieldset#edit-uc-product', context).drupalSetSummary(function(context) {
      var vals = [];
      $('input:checked', context).next('label').each(function() {
        vals.push(Drupal.checkPlain($(this).text()));
      });
      if (!$('#edit-uc-product-shippable', context).is(':checked')) {
        vals.unshift(Drupal.t('Not shippable'));
      }
      return vals.join(', ');
    });

    $('fieldset.product-field', context).drupalSetSummary(function(context) {
      var vals = [];

      if (Drupal.checkPlain($('#edit-model', context).val())) {
        vals.push(Drupal.t('SKU') + ': ' + Drupal.checkPlain($('#edit-model', context).val()));
      }

      if ($('#edit-shippable', context).is(':checked')) {
        vals.push(Drupal.t('Shippable'));
      }
      else {
        vals.push(Drupal.t('Not shippable'));
      }

      return vals.join(', ');
    });
  }
};

})(jQuery);