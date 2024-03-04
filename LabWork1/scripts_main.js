function checkGenEnabled(min_field, max_field, elem_count_field,
generate_but)
{
    if(min_field.failed || max_field.failed || elem_count_field.failed)
    {
        generate_but.enabled = false;
    }
    else
    {
        generate_but.enabled = true;
    }
}
