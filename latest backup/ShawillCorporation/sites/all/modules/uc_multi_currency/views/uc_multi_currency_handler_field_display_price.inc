<?php

class uc_multi_currency_handler_field_display_price extends uc_multi_currency_handler_field_price {

  /**
   * Overrides views_handler::option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['label']['default'] = t('Price');
    return $options;
  }

  /**
   * Overrides views_handler_field::get_value().
   */
  function get_value($values, $field = NULL) {
    $nid = parent::get_value($values, $field);
    $node = node_view(node_load($nid), 'teaser');
    return $node['display_price']['#value'];
  }

  /**
   * Overrides views_handler_field::render().
   */
  function render($values) {
    $product = $values->_field_data['nid']['entity'];
    $variant = empty($product->variant) ? _uc_product_get_variant($product) : $product;
    $tax = 0;
    if ($this->options['format'] == 'uc_multi_currency_price_add_vat') {
      $tax = uc_taxes_get_included_tax($variant);
      $tax = $tax[0];
    }
    $price = isset($variant->price) ? $variant->price + $tax : $variant->sell_price;

    if ($this->options['format'] == 'numeric') {
      return $price;
    }

    $suffix = '';
    if ($this->options['format'] == 'uc_multi_currency_price_vat') {
      if (module_exists('uc_vat') && uc_vat_vat_may_apply($product)) {
        $suffix = t(' + !tax', array('!tax' => variable_get('uc_vat_name', 'VAT')));
      }
    }

    $currency = isset($product->currency) ? $product->currency : uc_multi_currency_get_currency();
    return uc_multi_currency_format($price, $currency) . $suffix;
  }

}
