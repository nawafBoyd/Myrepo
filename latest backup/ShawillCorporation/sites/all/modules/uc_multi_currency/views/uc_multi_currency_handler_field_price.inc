<?php

class uc_multi_currency_handler_field_price extends views_handler_field_numeric {

  /**
   * Overrides views_handler::option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['format'] = array('default' => 'uc_multi_currency_price');
    return $options;
  }

  /**
   * Overrides views_handler::options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $options = $this->options;

    $form['format'] =  array(
      '#title' => t('Format'),
      '#type' => 'radios',
      '#options' => array(
        'uc_multi_currency_price' => t('Ubercart multi-currency price'),
        'uc_multi_currency_price_vat' => t('Ubercart multi-currency price (add VAT text)'),
        'uc_multi_currency_price_add_vat' => t('Ubercart multi-currency price (add VAT value)'),
        'numeric' => t('Numeric'),
      ),
      '#default_value' => $options['format'],
      '#weight' => 1,
    );

    // Change weight and dependency of the previous field on the parent numeric ones
    $weight = 2;
    foreach (array('set_precision', 'precision', 'decimal', 'separator', 'prefix', 'suffix') as $field) {
      if (isset($form[$field]['#dependency'])) {
        $form[$field]['#dependency'] += array('radio:options[format]' => array('numeric'));
        $form[$field]['#dependency_count'] = count($form[$field]['#dependency']);
      }
      else {
        $form[$field]['#dependency'] = array('radio:options[format]' => array('numeric'));
      }

      $form[$field]['#weight'] = ++$weight;
    }
  }

  /**
   * Overrides views_handler_field::render().
   */
  function render($values) {
    if ($this->options['format'] == 'numeric') {
      return parent::render($values);
    }

    $node = node_load($values->nid);
    $product = uc_product_load(array($node->nid => $node));
    $currency = isset($node->currency) ? $node->currency : uc_multi_currency_get_currency();
    $price = _uc_multi_currency_price_load($values->nid, $currency);
    $tax = 0;
    if ($this->options['format'] == 'uc_multi_currency_price_add_vat') {
      $tax = uc_taxes_get_included_tax($variant);
      $tax = $tax[0];
    }
    $prices = array(
      'uc_products_list_price' => isset($price->list_price) ? $price->list_price + $tax : 0,
      'uc_products_cost' => isset($price->cost) ? $price->cost + $tax : 0,
      'uc_products_sell_price' => isset($price->sell_price) ? $price->sell_price + $tax : 0,
    );
    $value = isset($prices[$this->field_alias]) ? $prices[$this->field_alias] : 0;
    $suffix = '';
    if ($this->options['format'] == 'uc_multi_currency_price_vat') {
      if (module_exists('uc_vat') && uc_vat_vat_may_apply($product)) {
        $suffix = t(' + !tax', array('!tax' => variable_get('uc_vat_name', 'VAT')));
      }
    }
    return uc_multi_currency_format($value, $currency) . $suffix;
  }

}
